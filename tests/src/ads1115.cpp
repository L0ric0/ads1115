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

TEST(ads1115, setRegConfig)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ADS1115::ADS1115_Config config {};

    config.mux = MUX::AIN0_AIN3;
    config.pga = PGA::FS_1_024;
    config.mode = MODE::CONT_CONV;
    config.data_rate = DR::SPS_16;
    config.comp_mode = COMP_MODE::WINDOW_COMP;
    config.comp_pol = COMP_POL::HIGH;
    config.comp_lat = COMP_LAT::LATCHING;
    config.comp_que = COMP_QUE::TWO_CONV;

    ads.setRegConfig(config);

    ASSERT_EQ(ads.getRegConfig().mux, MUX::AIN0_AIN3);
    ASSERT_EQ(ads.getRegConfig().pga, PGA::FS_1_024);
    ASSERT_EQ(ads.getRegConfig().mode, MODE::CONT_CONV);
    ASSERT_EQ(ads.getRegConfig().data_rate, DR::SPS_16);
    ASSERT_EQ(ads.getRegConfig().comp_mode, COMP_MODE::WINDOW_COMP);
    ASSERT_EQ(ads.getRegConfig().comp_pol, COMP_POL::HIGH);
    ASSERT_EQ(ads.getRegConfig().comp_lat, COMP_LAT::LATCHING);
    ASSERT_EQ(ads.getRegConfig().comp_que, COMP_QUE::TWO_CONV);
}
