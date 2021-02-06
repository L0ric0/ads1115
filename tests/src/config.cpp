// ads1115
#include "ads1115/config.hpp"

#include "ads1115/parameters.hpp"

// gtest
#include <gtest/gtest.h>

TEST(Config, to_bytes)
{
    ADS1115::Config config {};
    ASSERT_EQ(config.to_bytes(), uint16_t { 0x0583 });
}

TEST(Config, from_bytes)
{
    ADS1115::Config config(0x8583);
    ADS1115::Config def_config {};
    ASSERT_EQ(config.mux, def_config.mux);
    ASSERT_EQ(config.pga, def_config.pga);
    ASSERT_EQ(config.mode, def_config.mode);
    ASSERT_EQ(config.data_rate, def_config.data_rate);
    ASSERT_EQ(config.comp_mode, def_config.comp_mode);
    ASSERT_EQ(config.comp_pol, def_config.comp_pol);
    ASSERT_EQ(config.comp_lat, def_config.comp_lat);
    ASSERT_EQ(config.comp_que, def_config.comp_que);
}
