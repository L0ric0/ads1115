// ADS1115
#include "ads1115++/ads1115.hpp"

#include "ads1115++/config.hpp"
#include "ads1115++/fileno.hpp"
#include "ads1115++/parameters.hpp"

// stl
#include <cstdio>
#include <filesystem>
#include <fstream>
#include <linux/i2c-dev.h>
#include <stdexcept>
#include <string>
#include <sys/ioctl.h>

namespace ADS1115
{
    ADS1115::ADS1115(const std::filesystem::path& fs_dev, const ADDR addr)
        : m_device(std::fstream(fs_dev)),
          m_posix_handle(fileno(m_device))
    {
        setADDR(addr);
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
    }

    /***************************
     * Config register getters *
     ***************************/

    ADS1115_Config ADS1115::getRegConfig() const
    {
        return m_configuration;
    }

    /***************************
     * Config register setters *
     ***************************/

    void ADS1115::setRegConfig(const ADS1115_Config config)
    {
        m_configuration = config;
    }
} // namespace ADS1115
