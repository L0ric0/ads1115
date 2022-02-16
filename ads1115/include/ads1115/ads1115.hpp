#ifndef ADS1115_ADS1115_HPP_
#define ADS1115_ADS1115_HPP_

// ADS1115
#include "ads1115/config.hpp"
#include "ads1115/detail/ads1115_export.h"
#include "ads1115/threshold.hpp"

// i2c-device
#include "i2c-device/device.hpp"

// stl
#include <cstdio>
#include <filesystem>

namespace ADS1115
{

    /*! This class describes the ADS1115.
     * The data sheet of the ADS1115 can be fond at
     * https://cdn-shop.adafruit.com/datasheets/ads1115.pdf.
     */
    class ADS1115_EXPORT ADS1115
    {
        //! The generic i2c device in use.
        i2c::i2c_device<> m_device;

        //! The i2c bus address of the ADS1115.
        ADDR m_addr;

        //! The current configuration of the ADS1115.
        Config m_config {};

        //! The current configuration of the threshold registers.
        Threshold m_threshold {};

      public:
        /*! Creates the object to represent the ADS1115.
         *
         * This will open the device given by fs_dev and try to connect to the given i2c bus
         * address. The the configuration register of the ADS1115 is loaded and stored in the
         * object.
         *
         * \param fs_dev std::filesystem::path to the i2c bus device file.
         * \param addr Address of the ADS1115 on the i2c bus.
         */
        ADS1115(const int adapter_nr, const ADDR addr);

        ADS1115(const ADS1115& other) = delete;
        ADS1115(ADS1115&& other) noexcept;

        ADS1115& operator=(const ADS1115& other) = delete;
        ADS1115& operator=(ADS1115&& other) noexcept;

        //! Destroys the object that represents the ADS1115.
        ~ADS1115() = default;

        /*! Returns the address of the ADS1115 that is currently used.
         *
         * \returns ADDR that represents the currently used address.
         */
        ADDR getADDR() const;

        /*! Read the current value of the conversion register of the ADS1115.
         * If the ADS1115 is in single conversion mode a new conversion will be started and the
         * function returns when the conversion is done.
         *
         * \returns The value of the conversion register.
         */
        std::int16_t read() const;

        /*! Read the current voltage measured by the ADS1115.
         * If the ADS1115 is in single conversion mode a new conversion will be started and the
         * function returns when the conversion is done.
         *
         * \returns The voltage value.
         */
        double readVoltage() const;

        /*! Resets the device to it's default state.
         */
        void reset();

        /*! Converts a value returned by read() to a Voltage.
         *
         * Uses the current PGA setting for the conversion.
         *
         * \param value The value to be converted.
         * \returns The voltage value of the input.
         */
        double toVoltage(const std::int16_t value) const;

        /*! Converts a voltage value to a value returned by read(),
         *
         * Uses the current PGA setting for the conversion.
         *
         * \param value The value to be converted.
         * \returns The value in the same representation as returned by read().
         */
        std::int16_t fromVoltage(const double value) const;

        /***************************
         * Config register         *
         ***************************/

        /*! Read the config register of the ADS1115.
         *
         * Reads the current value of the config register of the ADS1115 and updates the internal
         * object representation of the config.
         *
         * \returns A Config object representing the content of the config register.
         */
        Config readRegConfig();

        /*! Returns the currently stored configuration of the ADS1115 without hiting the chip.
         *
         * \returns A Config object representing the content of the config register.
         */
        Config getRegConfig() const;

        /*! Sets the configuration of the ADS1115.
         *
         * Updates the internal object representation of the configuration and writes it to the
         * config register of the ADS1115.
         *
         * \param config A Config object representing the content of the config register.
         */
        void setRegConfig(const Config config);

        /**********************
         * Threshold register *
         **********************/

        /*! Read the threshold registers of the ADS1115.
         *
         * Reads the current value of the threshold registers of the ADS1115 and updates the
         * internal object representation.
         *
         * \returns A Threshold object representing the contents of the threshold registers.
         */
        Threshold readRegThreshold();

        /*! Returns the currently stored threshold registers of the ADS1115 whithout hiting the
         * chip.
         *
         * \returns A Threshold object representing the contents of the threshold registers.
         */
        Threshold getRegThreshold() const;

        /*! Sets the threshold registers of the ADS1115.
         *
         * Updates the internal object representation of the configuration and writes it to the
         * threshold registers of the ADS1115.
         *
         * \param threshold A Threshold object representing the contents of the threshold registers.
         */
        void setRegThreshold(const Threshold threshold);
    };

} // namespace ADS1115

#endif // ADS1115_ADS1115_HPP_
