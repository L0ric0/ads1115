#pragma once

// stl
#include <cstdint>
#include <map>

namespace ADS1115
{
    enum class ADDR { GND, VDD, SDA, SCL };

    enum class OS { NON, SINGLE_CONV };
    enum class MUX {
        AIN0_AIN1,
        AIN0_AIN3,
        AIN1_AIN3,
        AIN2_AIN3,
        AIN0_GND,
        AIN1_GND,
        AIN2_GND,
        AIN3_GND
    };
    enum class PGA { FS_6_144, FS_4_096, FS_2_048, FS_1_024, FS_0_512, FS_0_256 };
    enum class MODE { CONT_CONV, SINGLE_CONV };

    enum class DR { SPS_8, SPS_16, SPS_32, SPS_64, SPS_128, SPS_250, SPS_475, SPS_860 };
    enum class COMP_MODE { TRAD_COMP, WINDOW_COMP };
    enum class COMP_POL { LOW, HIGH };
    enum class COMP_LAT { NON_LATCHING, LATCHING };
    enum class COMP_QUE { ONE_CONV, TWO_CONV, FOUR_CONV, DISABLE_COMP };

    namespace detail
    {
        const std::map<ADDR, uint8_t> addr_map { { ADDR::GND, 0x48 },
                                                 { ADDR::VDD, 0x49 },
                                                 { ADDR::SDA, 0x4a },
                                                 { ADDR::SCL, 0x4b } };

        const std::map<OS, uint8_t> os_map { { OS::NON, 0x00 }, { OS::SINGLE_CONV, 0x80 } };

        const std::map<MUX, uint8_t> mux_map { { MUX::AIN0_AIN1, 0x00 }, { MUX::AIN0_AIN3, 0x10 },
                                               { MUX::AIN1_AIN3, 0x20 }, { MUX::AIN2_AIN3, 0x30 },
                                               { MUX::AIN0_GND, 0x40 },  { MUX::AIN1_GND, 0x50 },
                                               { MUX::AIN2_GND, 0x60 },  { MUX::AIN3_GND, 0x70 }

        };
        const std::map<PGA, uint8_t> pga_map {
            { PGA::FS_6_144, 0x00 }, { PGA::FS_4_096, 0x02 }, { PGA::FS_2_048, 0x04 },
            { PGA::FS_1_024, 0x06 }, { PGA::FS_0_512, 0x08 }, { PGA::FS_0_256, 0x0a },
        };
        const std::map<MODE, uint8_t> mode_map { { MODE::CONT_CONV, 0x00 },
                                                 { MODE::SINGLE_CONV, 0x01 } };

        const std::map<DR, uint8_t> dr_map {
            { DR::SPS_8, 0x00 },   { DR::SPS_16, 0x20 },  { DR::SPS_32, 0x40 },
            { DR::SPS_64, 0x60 },  { DR::SPS_128, 0x80 }, { DR::SPS_250, 0xa0 },
            { DR::SPS_475, 0xc0 }, { DR::SPS_860, 0xe0 },
        };
        const std::map<COMP_MODE, uint8_t> comp_mode_map { { COMP_MODE::TRAD_COMP, 0x00 },
                                                           { COMP_MODE::WINDOW_COMP, 0x10 } };
        const std::map<COMP_POL, uint8_t> comp_pol_map { { COMP_POL::LOW, 0x00 },
                                                         { COMP_POL::HIGH, 0x08 } };
        const std::map<COMP_LAT, uint8_t> comp_lat_map { { COMP_LAT::NON_LATCHING, 0x00 },
                                                         { COMP_LAT::LATCHING, 0x04 } };
        const std::map<COMP_QUE, uint8_t> comp_que_map { { COMP_QUE::ONE_CONV, 0x00 },
                                                         { COMP_QUE::TWO_CONV, 0x01 },
                                                         { COMP_QUE::FOUR_CONV, 0x02 },
                                                         { COMP_QUE::DISABLE_COMP, 0x03 } };

    } // namespace detail
} // namespace ADS1115
