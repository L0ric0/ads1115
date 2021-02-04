// ADS1115
#include "ads1115++/ads1115.hpp"

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
        : device_(std::fstream(fs_dev)),
          posix_handle_(fileno(device_))
    {
        setADDR(addr);
    }

    ADDR ADS1115::getADDR() const
    {
        return addr_;
    }

    void ADS1115::setADDR(const ADDR addr)
    {
        addr_ = addr;

        // For this device it seems to be impossible to check if the a ADS1115 is listening on the
        // address. This is due to the fact that ioctl returns 0 as long as a ADS1115 is connected
        // and one of the possible addresses is supplied.
        if (ioctl(posix_handle_, I2C_SLAVE, detail::addr_map.at(addr_)) < 0) {
            // FIXME turn into a device_error
            throw std::runtime_error("Couldn't find device on address!");
        }
    }

    /***************************
     * Config register getters *
     ***************************/

    OS ADS1115::getRegConfigOS() const
    {
        return reg_config_os_;
    }

    MUX ADS1115::getRegConfigMUX() const
    {
        return reg_config_mux_;
    }

    PGA ADS1115::getRegConfigPGA() const
    {
        return reg_config_pga_;
    }

    MODE ADS1115::getRegConfigMode() const
    {
        return reg_config_mode_;
    }

    DR ADS1115::getRegConfigDR() const
    {
        return reg_config_dr_;
    }

    COMP_MODE ADS1115::getRegConfigCompMode() const
    {
        return reg_config_comp_mode_;
    }

    COMP_POL ADS1115::getRegConfigCompPol() const
    {
        return reg_config_comp_pol_;
    }

    COMP_LAT ADS1115::getRegConfigCompLat() const
    {
        return reg_config_comp_lat_;
    }

    COMP_QUE ADS1115::getRegConfigCompQue() const
    {
        return reg_config_comp_que_;
    }

    /***************************
     * Config register setters *
     ***************************/

    void ADS1115::setRegConfigOS(const OS os)
    {
        if (reg_config_mode_ != MODE::SINGLE_CONV) {
            throw std::runtime_error(
                "Setting the OS register is only allowed in power-down single-shot mode.");
        }
        reg_config_os_ = os;
    }

    void ADS1115::setRegConfigMUX(const MUX mux)
    {
        reg_config_mux_ = mux;
    }

    void ADS1115::setRegConfigPGA(const PGA pga)
    {
        reg_config_pga_ = pga;
    }

    void ADS1115::setRegConfigMode(const MODE mode)
    {
        reg_config_mode_ = mode;
    }

    void ADS1115::setRegConfigDR(const DR data_rate)
    {
        reg_config_dr_ = data_rate;
    }

    void ADS1115::setRegConfigCompMode(const COMP_MODE comp_mode)
    {
        reg_config_comp_mode_ = comp_mode;
    }

    void ADS1115::setRegConfigCompPol(const COMP_POL comp_pol)
    {
        reg_config_comp_pol_ = comp_pol;
    }

    void ADS1115::setRegConfigCompLat(const COMP_LAT comp_lat)
    {
        reg_config_comp_lat_ = comp_lat;
    }

    void ADS1115::setRegConfigCompQue(const COMP_QUE comp_que)
    {
        reg_config_comp_que_ = comp_que;
    }
} // namespace ADS1115
