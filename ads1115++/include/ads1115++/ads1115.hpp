#ifndef ADS1115_ADS1115_HPP_
#define ADS1115_ADS1115_HPP_

// ADS1115
#include "ads1115++/config.hpp"

// stl
#include <filesystem>
#include <fstream>

namespace ADS1115
{

    class ADS1115
    {
      public:
        ADS1115(const std::filesystem::path& fs_dev, const ADDR addr);

        ADDR getADDR() const;
        void setADDR(const ADDR addr);

        int16_t readRegConversion();

        /***************************
         * Config register         *
         ***************************/

        void readRegConfig();

        ADS1115_Config getRegConfig() const;
        void setRegConfig(const ADS1115_Config config);

        /**********************
         * Threshold register *
         **********************/

        void readRegThreshLo();
        void readRegThreshHi();

        int16_t getRegThreshLo() const;
        int16_t getRegThreshHi() const;

        void setRegThreshLo(const int16_t low_threshold);
        void setRegThreshHi(const int16_t high_threshold);

      private:
        const std::fstream m_device;
        const int m_posix_handle;

        ADDR m_addr;

        ADS1115_Config m_configuration;
    };

} // namespace ADS1115

#endif // ADS1115_ADS1115_HPP_
