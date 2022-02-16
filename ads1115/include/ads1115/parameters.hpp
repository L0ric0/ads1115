#ifndef ADS1115_PARAMETERS_HPP_
#define ADS1115_PARAMETERS_HPP_

// stl
#include <cstdint>
#include <unordered_map>

namespace ADS1115
{
    //! Address of the conversion register.
    constexpr std::uint8_t conv_reg_addr = 0x00;
    //! Address of the config register.
    constexpr std::uint8_t conf_reg_addr = 0x01;
    //! Address of the low threshold register.
    constexpr std::uint8_t lo_thresh_reg_addr = 0x02;
    //! Address of the high threshold register.
    constexpr std::uint8_t hi_thresh_reg_addr = 0x03;

    //! This Enum describes the possible i2c bus addresses of a ADS1115.
    enum class ADDR : std::uint8_t {
        GND = 0x48,
        VDD = 0x49,
        SDA = 0x4a,
        SCL = 0x4b,
    };

    /*! This Enum describes the possible values that can be writen to the operational status
     * bit while the ADS1115 is in power down mode.
     *
     * The operational status bit of the config register can only be writen when the ADS1115 is in
     * power down mode.
     */
    enum class OS : std::uint16_t {
        //! No effect when the config register is writen.
        NON = 0x0000,
        //! Starts a new conversion when the conversion register is writen.
        SINGLE_CONV = 0x8000,
    };

    /*! This enum describes the possible values of the multiplexer bits of the configuration
     * register. It is used to select the inputs from which the ADS1115 reads data.
     */
    enum class MUX : std::uint16_t {
        AIN0_AIN1 = 0x0000,
        AIN0_AIN3 = 0x1000,
        AIN1_AIN3 = 0x2000,
        AIN2_AIN3 = 0x3000,
        AIN0_GND = 0x4000,
        AIN1_GND = 0x5000,
        AIN2_GND = 0x6000,
        AIN3_GND = 0x7000,
    };

    /*! This enum describes the possible values for the programable gain amplifier bits of the
     * config register. This effectefly defines the full-scale of the analog inputs above which the
     * output will be cliped.
     */
    enum class PGA : std::uint16_t {
        //! FS = \f$\pm\f$ 6.144V
        FS_6_144 = 0x0000,
        //! FS = \f$\pm\f$ 4.096V
        FS_4_096 = 0x0200,
        //! FS = \f$\pm\f$ 2.048V
        FS_2_048 = 0x0400,
        //! FS = \f$\pm\f$ 1.024V
        FS_1_024 = 0x0600,
        //! FS = \f$\pm\f$ 0.512V
        FS_0_512 = 0x0800,
        //! FS = \f$\pm\f$ 0.256V
        FS_0_256 = 0x0a00,
    };

    /*! This enum describes the operational modes of the ADS1115.
     */
    enum class MODE : std::uint16_t {
        //! Sets the ADS1115 to continuous conversion mode.
        CONT_CONV = 0x0000,
        //! Sets the ADS1115 to power-down single-shot mode.
        SINGLE_CONV = 0x0100,
    };

    /*! This enum describes the possible data rates of the ADS1115.
     */
    enum class DR : std::uint16_t {
        //! DR = 8 SPS
        SPS_8 = 0x0000,
        //! DR = 16 SPS
        SPS_16 = 0x0020,
        //! DR = 32 SPS
        SPS_32 = 0x0040,
        //! DR = 64 SPS
        SPS_64 = 0x0060,
        //! DR = 128 SPS
        SPS_128 = 0x0080,
        //! DR = 250 SPS
        SPS_250 = 0x00a0,
        //! DR = 475 SPS
        SPS_475 = 0x00c0,
        //! DR = 860 SPS
        SPS_860 = 0x00e0,
    };

    /*! This enum describes the mode of the comparator of the ADS1115.
     */
    enum class COMP_MODE : std::uint16_t {
        //! Traditional comparator with hysteresis
        TRAD_COMP = 0x0000,
        //! Window comparator
        WINDOW_COMP = 0x0010,
    };

    /*! This enum describes the comparator polarity of the ADS1115.
     * This enum controls the polarity of the ALERT/RDY pin. When COMP_POL::LOW the comparator
     * output is active low. When COMP_POL::HIGH the ALERT/RDY pin is active high.
     */
    enum class COMP_POL : std::uint16_t {
        LOW = 0x0000,
        HIGH = 0x0008,
    };

    /*! This enum describes the latching behaviour of the comparator.
     * This enum controls whether the ALERT/RDY pin latches once asserted or clears once conversions
     * are within the margin of the upper and lower threshold values. When COMP_LAT::NON_LATCHING,
     * the ALERT/RDY pin does not latch when asserted. When COMP_LAT::LATCHING, the asserted
     * ALERT/RDY pin remains latched until conversion data are read by the master or an appropriate
     * SMBus alert response is sent by the master, the device responds with its address, and it is
     * the lowest address currently asserting the ALERT/RDY bus line.
     */
    enum class COMP_LAT : std::uint16_t {
        NON_LATCHING = 0x0000,
        LATCHING = 0x0004,
    };

    /*! This enum describes the state of the comparator queue.
     * This enum performs two functions. When set to COMP_QUE::DISABLE_COMP, they disable the
     * comparator function and put the ALERT/RDY pin into a high state. When set to any other value,
     * they control the number of successive conversions exceeding the upper or lower thresholds
     * required before asserting the ALERT/RDY pin.
     */
    enum class COMP_QUE : std::uint16_t {
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
