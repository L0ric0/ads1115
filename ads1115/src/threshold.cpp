// ADS1115
#include "ads1115/threshold.hpp"

#include "ads1115/bit.hpp"

// stl
#include <cstdint>
#include <stdexcept>

namespace ADS1115
{
    Threshold::Threshold(const std::int16_t low, const std::int16_t high)
    {
        set(low, high);
    }

    void Threshold::set(const std::int16_t low, const std::int16_t high)
    {
        if ((util::bit_cast<std::uint16_t, std::int16_t>(high) & 0x8000)
            and !(util::bit_cast<std::uint16_t, std::int16_t>(low) & 0x8000)) {
            m_high = high;
            m_low = low;
            return;
        }
        if (high < low) {
            throw std::runtime_error("The high threshold has to be bigger than the low threshold.");
        }
        m_high = high;
        m_low = low;
    }

    std::int16_t Threshold::getHigh() const
    {
        return m_high;
    }
    std::int16_t Threshold::getLow() const
    {
        return m_low;
    }
} // namespace ADS1115
