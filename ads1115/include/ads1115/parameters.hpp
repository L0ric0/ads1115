#ifndef ADS1115_PARAMETERS_HPP_
#define ADS1115_PARAMETERS_HPP_

// stl
#include <cstdint>
#include <unordered_map>

namespace ADS1115
{
    constexpr uint8_t conv_reg_addr = 0x00;
    constexpr uint8_t conf_reg_addr = 0x01;
    constexpr uint8_t lo_thresh_reg_addr = 0x02;
    constexpr uint8_t hi_thresh_reg_addr = 0x03;

    enum class ADDR : uint8_t {
        GND = 0x48,
        VDD = 0x49,
        SDA = 0x4a,
        SCL = 0x4b,
    };

    enum class OS : uint16_t {
        NON = 0x0000,
        SINGLE_CONV = 0x8000,
    };
    enum class MUX : uint16_t {
        AIN0_AIN1 = 0x0000,
        AIN0_AIN3 = 0x1000,
        AIN1_AIN3 = 0x2000,
        AIN2_AIN3 = 0x3000,
        AIN0_GND = 0x4000,
        AIN1_GND = 0x5000,
        AIN2_GND = 0x6000,
        AIN3_GND = 0x7000,
    };
    enum class PGA : uint16_t {
        FS_6_144 = 0x0000,
        FS_4_096 = 0x0200,
        FS_2_048 = 0x0400,
        FS_1_024 = 0x0600,
        FS_0_512 = 0x0800,
        FS_0_256 = 0x0a00,
    };
    enum class MODE : uint16_t {
        CONT_CONV = 0x0000,
        SINGLE_CONV = 0x0100,
    };

    enum class DR : uint16_t {
        SPS_8 = 0x0000,
        SPS_16 = 0x0020,
        SPS_32 = 0x0040,
        SPS_64 = 0x0060,
        SPS_128 = 0x0080,
        SPS_250 = 0x00a0,
        SPS_475 = 0x00c0,
        SPS_860 = 0x00e0,
    };
    enum class COMP_MODE : uint16_t {
        TRAD_COMP = 0x0000,
        WINDOW_COMP = 0x0010,
    };
    enum class COMP_POL : uint16_t {
        LOW = 0x0000,
        HIGH = 0x0008,
    };
    enum class COMP_LAT : uint16_t {
        NON_LATCHING = 0x0000,
        LATCHING = 0x0004,
    };
    enum class COMP_QUE : uint16_t {
        ONE_CONV = 0x0000,
        TWO_CONV = 0x0001,
        FOUR_CONV = 0x0002,
        DISABLE_COMP = 0x0003,
    };

    const static std::unordered_map<PGA, double> pga_voltage_map {
        { PGA::FS_6_144, 6.144 }, { PGA::FS_4_096, 4.096 }, { PGA::FS_2_048, 2.048 },
        { PGA::FS_1_024, 1.024 }, { PGA::FS_0_512, 0.512 }, { PGA::FS_0_256, 0.256 },
    };
} // namespace ADS1115

#endif // ADS1115_PARAMETERS_HPP_
