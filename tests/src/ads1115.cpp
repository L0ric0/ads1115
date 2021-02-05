// ads1115
#include "ads1115++/ads1115.hpp"

#include "ads1115++/config.hpp"
#include "ads1115++/parameters.hpp"

// gtest
#include <gtest/gtest.h>

using namespace ADS1115;

TEST(ads1115, create)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ASSERT_EQ(ads.getADDR(), ADDR::GND);
}

TEST(ads1115, setAddr)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ads.setADDR(ADDR::SDA);
    ASSERT_EQ(ads.getADDR(), ADDR::SDA);
}

TEST(ads1115, getRegConfig)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ADS1115::ADS1115_Config def_config {};

    ASSERT_EQ(ads.getRegConfig().mux, MUX::AIN0_AIN1);
    ASSERT_EQ(ads.getRegConfig().pga, PGA::FS_2_048);
    ASSERT_EQ(ads.getRegConfig().mode, MODE::SINGLE_CONV);
    ASSERT_EQ(ads.getRegConfig().data_rate, DR::SPS_128);
    ASSERT_EQ(ads.getRegConfig().comp_mode, COMP_MODE::TRAD_COMP);
    ASSERT_EQ(ads.getRegConfig().comp_pol, COMP_POL::LOW);
    ASSERT_EQ(ads.getRegConfig().comp_lat, COMP_LAT::NON_LATCHING);
    ASSERT_EQ(ads.getRegConfig().comp_que, COMP_QUE::DISABLE_COMP);
}

TEST(ads1115, getRegThreshold)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ASSERT_EQ(ads.getRegThreshold().getHigh(), 32767);
    ASSERT_EQ(ads.getRegThreshold().getLow(), -32768);
}
