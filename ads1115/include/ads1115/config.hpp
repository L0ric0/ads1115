#ifndef ADS1115_OPTIONS_HPP_
#define ADS1115_OPTIONS_HPP_

// ADS1115
#include "ads1115/detail/ads1115_export.h"
#include "ads1115/parameters.hpp"

// stl
#include <cstdint>

namespace ADS1115
{
    /*! The Config struct represents the config register of the ADS1115.
     *
     * The config register of the ADS1115 is consists of 16 bit which configure the device. The
     * members of this struct map to the configuration options described in the datasheet and can
     * span more than one bit. A `to_bytes()` member function is provided to convert the struct to a
     * `std::uint16_t` which can be writen to the config register of the ADS1115.
     */
    struct ADS1115_EXPORT Config {

        Config() = default;
        Config(const std::uint16_t bytes);

        MUX mux = MUX::AIN0_AIN1;
        PGA pga = PGA::FS_2_048;
        MODE mode = MODE::SINGLE_CONV;
        DR data_rate = DR::SPS_128;
        COMP_MODE comp_mode = COMP_MODE::TRAD_COMP;
        COMP_POL comp_pol = COMP_POL::LOW;
        COMP_LAT comp_lat = COMP_LAT::NON_LATCHING;
        COMP_QUE comp_que = COMP_QUE::DISABLE_COMP;

        bool operator==(const Config& other) const = default;

        /*! Converts the struct to a `std::uint16_t` which can be writen to the config register of
         * the ADS1115.
         */
        std::uint16_t to_bytes() const;
    };
} // namespace ADS1115

#endif // ADS1115_OPTIONS_HPP_
