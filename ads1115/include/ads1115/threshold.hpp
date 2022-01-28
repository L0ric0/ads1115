#ifndef ADS1115_THRESHOLD_HPP_
#define ADS1115_THRESHOLD_HPP_

//ads1115
#include "ads1115/detail/ads1115_export.h"

// stl
#include <cstdint>

namespace ADS1115
{
    class ADS1115_EXPORT Threshold
    {
        int16_t m_high = 32767;
        int16_t m_low = -32768;

      public:
        Threshold() = default;
        Threshold(const int16_t low, const int16_t high);

        bool operator==(const Threshold& other) const = default;

        void set(const int16_t low, const int16_t high);
        int16_t getHigh() const;
        int16_t getLow() const;
    };
} // namespace ADS1115

#endif
