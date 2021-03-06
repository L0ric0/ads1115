// ADS1115
#include "ads1115/ads1115.hpp"

#include "ads1115/bit.hpp"
#include "ads1115/config.hpp"
#include "ads1115/parameters.hpp"

// linux
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern "C" {
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
}

// stl
#include <bit>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <thread>

namespace ADS1115
{
    ADS1115::ADS1115(const std::filesystem::path& fs_dev, const ADDR addr)
        : m_posix_handle(open(fs_dev.c_str(), O_RDWR))
    {
        if (m_posix_handle < 0) {
            throw std::runtime_error("Unable to open i2c device.");
        }
        setADDR(addr);
    }

    ADS1115::~ADS1115()
    {
        close(m_posix_handle);
    }

    ADDR ADS1115::getADDR() const
    {
        return m_addr;
    }

    void ADS1115::setADDR(const ADDR addr)
    {
        m_addr = addr;

        // For this device it seems to be impossible to check if the a ADS1115 is listening on the
        // address. This is due to the fact that ioctl returns 0 as long as a ADS1115 is connected
        // and one of the possible addresses is supplied.
        if (ioctl(m_posix_handle, I2C_SLAVE, static_cast<uint8_t>(m_addr)) < 0) {
            // FIXME turn into a device_error
            throw std::runtime_error("Couldn't find device on address!");
        }
        readRegConfig();
        readRegThreshold();
    }

    int16_t ADS1115::read() const
    {
        if (m_config.mode == MODE::SINGLE_CONV) {
            // to start a conversion in single conversion mode the MSB of the config
            // register has to be set
            write_word(conf_reg_addr, m_config.to_bytes() | 0x8000);
            // when the conversion starts the ADS1115 resets the MSB and sets it when the conversion
            // is done
            while (!(read_word(conf_reg_addr) & 0x8000)) {
                // poll every millisecond, as the shortest conversion the device can do takes 1.2ms
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        uint16_t data = read_word(conv_reg_addr);

        return util::bit_cast<int16_t, uint16_t>(data);
    }

    double ADS1115::readVoltage() const
    {
        return toVoltage(read());
    }

    void ADS1115::reset()
    {
        Config config {};
        setRegConfig(config);

        Threshold threshold {};
        setRegThreshold(threshold);
    }

    double ADS1115::toVoltage(const int16_t value) const
    {
        return value * pga_voltage_map.at(m_config.pga) / 32768;
    }

    int16_t ADS1115::fromVoltage(const double value) const
    {
        return static_cast<int16_t>(value * 32768 / pga_voltage_map.at(m_config.pga));
    }

    /*******************
     * Config register *
     *******************/

    Config ADS1115::readRegConfig()
    {
        const uint16_t config_word = read_word(conf_reg_addr);
        Config config(config_word);
        m_config = config;
        return config;
    }

    Config ADS1115::getRegConfig() const
    {
        return m_config;
    }

    void ADS1115::setRegConfig(const Config config)
    {
        write_word(conf_reg_addr, m_config.to_bytes());
        m_config = config;
    }

    /**********************
     * Threshold register *
     **********************/

    Threshold ADS1115::readRegThreshold()
    {
        uint16_t low_threshold = read_word(lo_thresh_reg_addr);
        uint16_t high_threshold = read_word(hi_thresh_reg_addr);

        Threshold threshold {
            util::bit_cast<int16_t, uint16_t>(low_threshold),
            util::bit_cast<int16_t, uint16_t>(high_threshold),
        };

        m_threshold = threshold;
        return threshold;
    }

    Threshold ADS1115::getRegThreshold() const
    {
        return m_threshold;
    }

    void ADS1115::setRegThreshold(const Threshold threshold)
    {
        write_word(lo_thresh_reg_addr, util::bit_cast<uint16_t, int16_t>(threshold.getLow()));
        write_word(hi_thresh_reg_addr, util::bit_cast<uint16_t, int16_t>(threshold.getHigh()));
        m_threshold = threshold;
    }

    uint16_t ADS1115::read_word(const uint8_t reg_addr) const
    {
        int32_t data = i2c_smbus_read_word_data(m_posix_handle, reg_addr);
        if (0 > data) {
            throw std::runtime_error("Error reading value from i2c device.");
        }
        return util::from_device_repr(static_cast<uint16_t>(data));
    }

    void ADS1115::write_word(const uint8_t reg_addr, const uint16_t value) const
    {
        uint16_t data = util::to_device_repr(value);
        if (0 > i2c_smbus_write_word_data(m_posix_handle, reg_addr, data)) {
            throw std::runtime_error("Error writing value to i2c device.");
        }
    }
} // namespace ADS1115
