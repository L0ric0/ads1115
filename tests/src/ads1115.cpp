// ads1115
#include "ads1115++/ads1115.hpp"

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

    ASSERT_EQ(ads.getRegConfigMUX(), MUX::AIN0_AIN1);
    ASSERT_EQ(ads.getRegConfigPGA(), PGA::FS_2_048);
    ASSERT_EQ(ads.getRegConfigMode(), MODE::SINGLE_CONV);
    ASSERT_EQ(ads.getRegConfigDR(), DR::SPS_128);
    ASSERT_EQ(ads.getRegConfigCompMode(), COMP_MODE::TRAD_COMP);
    ASSERT_EQ(ads.getRegConfigCompPol(), COMP_POL::LOW);
    ASSERT_EQ(ads.getRegConfigCompLat(), COMP_LAT::NON_LATCHING);
    ASSERT_EQ(ads.getRegConfigCompQue(), COMP_QUE::DISABLE_COMP);
}

TEST(ads1115, setRegConfig)
{
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);

    ads.setRegConfigMUX(MUX::AIN0_AIN3);
    ASSERT_EQ(ads.getRegConfigMUX(), MUX::AIN0_AIN3);

    ads.setRegConfigPGA(PGA::FS_1_024);
    ASSERT_EQ(ads.getRegConfigPGA(), PGA::FS_1_024);

    ads.setRegConfigMode(MODE::CONT_CONV);
    ASSERT_EQ(ads.getRegConfigMode(), MODE::CONT_CONV);

    ads.setRegConfigDR(DR::SPS_16);
    ASSERT_EQ(ads.getRegConfigDR(), DR::SPS_16);

    ads.setRegConfigCompMode(COMP_MODE::WINDOW_COMP);
    ASSERT_EQ(ads.getRegConfigCompMode(), COMP_MODE::WINDOW_COMP);

    ads.setRegConfigCompPol(COMP_POL::HIGH);
    ASSERT_EQ(ads.getRegConfigCompPol(), COMP_POL::HIGH);

    ads.setRegConfigCompLat(COMP_LAT::LATCHING);
    ASSERT_EQ(ads.getRegConfigCompLat(), COMP_LAT::LATCHING);

    ads.setRegConfigCompQue(COMP_QUE::TWO_CONV);
    ASSERT_EQ(ads.getRegConfigCompQue(), COMP_QUE::TWO_CONV);
}

TEST(ads1115, setRegConfigOS){
    ADS1115::ADS1115 ads("/dev/i2c-1", ADDR::GND);
    ads.setRegConfigOS(OS::NON);
    ASSERT_EQ(ads.getRegConfigOS(), OS::NON);

    ads.setRegConfigMode(MODE::CONT_CONV);
    ASSERT_THROW(ads.setRegConfigOS(OS::SINGLE_CONV), std::runtime_error);
}
