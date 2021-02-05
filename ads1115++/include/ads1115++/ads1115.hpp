#ifndef ADS1115_ADS1115_HPP_
#define ADS1115_ADS1115_HPP_

// ADS1115
#include "ads1115++/config.hpp"
#include "ads1115++/threshold.hpp"

// stl
#include <cstdio>
#include <filesystem>

namespace ADS1115
{

    class ADS1115
    {
        const int m_posix_handle;

        ADDR m_addr;

        ADS1115_Config m_config {};

        Threshold m_threshold {};

      public:
        ADS1115(const std::filesystem::path& fs_dev, const ADDR addr);
        ~ADS1115();

        ADDR getADDR() const;
        void setADDR(const ADDR addr);

        int16_t read() const;

        /***************************
         * Config register         *
         ***************************/

        ADS1115_Config readRegConfig();

        ADS1115_Config getRegConfig() const;
        void setRegConfig(const ADS1115_Config config);

        /**********************
         * Threshold register *
         **********************/

        Threshold readRegThreshold();

        Threshold getRegThreshold() const;

        void setRegThreshold(const Threshold threshold);

      private:
        uint16_t read_word(const uint8_t reg_addr) const;
        void write_word(const uint8_t reg_addr, const uint16_t value) const;
    };

} // namespace ADS1115

#endif // ADS1115_ADS1115_HPP_
