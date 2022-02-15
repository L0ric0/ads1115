// ADS1115
#include "ads1115/ads1115.hpp"

#include "ads1115/bit.hpp"
#include "ads1115/config.hpp"
#include "ads1115/parameters.hpp"

// i2c-device
#include "i2c-device/device.hpp"
#include "i2c-device/util.hpp"

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
    ADS1115::ADS1115(const int adapter_nr, const ADDR addr)
        : m_device(i2c::AdapterNumber(adapter_nr), i2c::DeviceID(static_cast<int>(addr))),
          m_addr(addr)
    {
    }

    ADS1115::ADS1115(ADS1115&& other) noexcept
        : m_device(std::move(other.m_device)),
          m_addr(other.m_addr),
          m_config(other.m_config),
          m_threshold(other.m_threshold)
    {
    }

    ADS1115& ADS1115::operator=(ADS1115&& other) noexcept
    {
        m_device = std::move(other.m_device);
        m_addr = std::move(other.m_addr);
        m_config = std::move(other.m_config);
        m_threshold = std::move(other.m_threshold);

        return *this;
    }

    ADDR ADS1115::getADDR() const
    {
        return m_addr;
    }

    std::int16_t ADS1115::read() const
    {
        if (m_config.mode == MODE::SINGLE_CONV) {
            // to start a conversion in single conversion mode the MSB of the config
            // register has to be set
            m_device.write_word_data(conf_reg_addr, m_config.to_bytes() | 0x8000);
            // when the conversion starts the ADS1115 resets the MSB and sets it when the conversion
            // is done
            while (!(m_device.read_word_data(conf_reg_addr) & 0x8000)) {
                // poll every millisecond, as the shortest conversion the device can do takes 1.2ms
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
            }
        }

        std::uint16_t data = m_device.read_word_data(conv_reg_addr);

        return std::bit_cast<std::int16_t>(data);
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

    double ADS1115::toVoltage(const std::int16_t value) const
    {
        return value * pga_voltage_map.at(m_config.pga) / 32768;
    }

    std::int16_t ADS1115::fromVoltage(const double value) const
    {
        return static_cast<std::int16_t>(value * 32768 / pga_voltage_map.at(m_config.pga));
    }

    /*******************
     * Config register *
     *******************/

    Config ADS1115::readRegConfig()
    {
        const std::uint16_t config_word = m_device.read_word_data(conf_reg_addr);
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
        m_device.write_word_data(conf_reg_addr, m_config.to_bytes());
        m_config = config;
    }

    /**********************
     * Threshold register *
     **********************/

    Threshold ADS1115::readRegThreshold()
    {
        std::uint16_t low_threshold = m_device.read_word_data(lo_thresh_reg_addr);
        std::uint16_t high_threshold = m_device.read_word_data(hi_thresh_reg_addr);

        Threshold threshold {
            std::bit_cast<std::int16_t>(low_threshold),
            std::bit_cast<std::int16_t>(high_threshold),
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
        m_device.write_word_data(lo_thresh_reg_addr, std::bit_cast<std::uint16_t>(threshold.getLow()));
        m_device.write_word_data(hi_thresh_reg_addr, std::bit_cast<std::uint16_t>(threshold.getHigh()));
        m_threshold = threshold;
    }

} // namespace ADS1115
