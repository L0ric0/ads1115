#ifndef ADS1115_THRESHOLD_HPP_
#define ADS1115_THRESHOLD_HPP_

// ADS1115
#include "ads1115++/bit.hpp"

// stl
#include <cstdint>

namespace ADS1115
{
    struct Threshold {
        int16_t high = 32767;
        int16_t low = -32768;
    };
} // namespace ADS1115

#endif
