// ADS1115
#include "ads1115/config.hpp"

#include "ads1115/parameters.hpp"

// stl
#include <cstdint>

namespace ADS1115
{
    Config::Config(const uint16_t bytes)
        : mux(static_cast<MUX>(0x7000 & bytes)),
          pga(static_cast<PGA>(0x0e00 & bytes)),
          mode(static_cast<MODE>(0x0100 & bytes)),
          data_rate(static_cast<DR>(0x00e0 & bytes)),
          comp_mode(static_cast<COMP_MODE>(0x0010 & bytes)),
          comp_pol(static_cast<COMP_POL>(0x0008 & bytes)),
          comp_lat(static_cast<COMP_LAT>(0x0004 & bytes)),
          comp_que(static_cast<COMP_QUE>(0x0003 & bytes))
    {
    }

    uint16_t Config::to_bytes() const
    {
        return static_cast<uint16_t>(mux) | static_cast<uint16_t>(pga) | static_cast<uint16_t>(mode)
               | static_cast<uint16_t>(data_rate) | static_cast<uint16_t>(comp_mode)
               | static_cast<uint16_t>(comp_pol) | static_cast<uint16_t>(comp_lat)
               | static_cast<uint16_t>(comp_que);
    }
} // namespace ADS1115
