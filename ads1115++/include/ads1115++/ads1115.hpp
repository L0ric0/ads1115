#ifndef ADS1115_ADS1115_HPP_
#define ADS1115_ADS1115_HPP_

// ADS1115
#include "ads1115++/parameters.hpp"

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

        /***************************
         * Config register getters *
         ***************************/

        OS getRegConfigOS() const;
        MUX getRegConfigMUX() const;
        PGA getRegConfigPGA() const;
        MODE getRegConfigMode() const;
        DR getRegConfigDR() const;
        COMP_MODE getRegConfigCompMode() const;
        COMP_POL getRegConfigCompPol() const;
        COMP_LAT getRegConfigCompLat() const;
        COMP_QUE getRegConfigCompQue() const;

        /***************************
         * Config register setters *
         ***************************/
        void setRegConfigOS(const OS os);
        void setRegConfigMUX(const MUX mux);
        void setRegConfigPGA(const PGA gain);
        void setRegConfigMode(const MODE mode);
        void setRegConfigDR(const DR data_rate);
        void setRegConfigCompMode(const COMP_MODE comp_mode);
        void setRegConfigCompPol(const COMP_POL comp_pol);
        void setRegConfigCompLat(const COMP_LAT comp_lat);
        void setRegConfigCompQue(const COMP_QUE comp_que);

      private:
        const std::fstream device_;
        const int posix_handle_;

        ADDR addr_;

        OS reg_config_os_;
        MUX reg_config_mux_ = MUX::AIN0_AIN1;
        PGA reg_config_pga_ = PGA::FS_2_048;
        MODE reg_config_mode_ = MODE::SINGLE_CONV;
        DR reg_config_dr_ = DR::SPS_128;
        COMP_MODE reg_config_comp_mode_ = COMP_MODE::TRAD_COMP;
        COMP_POL reg_config_comp_pol_ = COMP_POL::LOW;
        COMP_LAT reg_config_comp_lat_ = COMP_LAT::NON_LATCHING;
        COMP_QUE reg_config_comp_que_ = COMP_QUE::DISABLE_COMP;
    };

} // namespace ADS1115

#endif // ADS1115_ADS1115_HPP_
