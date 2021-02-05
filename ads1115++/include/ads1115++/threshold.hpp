#ifndef ADS1115_THRESHOLD_HPP_
#define ADS1115_THRESHOLD_HPP_

// stl
#include <cstdint>

namespace ADS1115
{
    class Threshold
    {
        int16_t m_high = 32767;
        int16_t m_low = -32768;

      public:
        Threshold() = default;
        Threshold(const int16_t low, const int16_t high);

        void set(const int16_t low, const int16_t high);
        int16_t getHigh() const;
        int16_t getLow() const;
    };
} // namespace ADS1115

#endif
