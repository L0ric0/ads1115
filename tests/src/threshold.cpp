// ads1115
#include "ads1115/threshold.hpp"

// gtest
#include <gtest/gtest.h>

// stl
#include <stdexcept>

using namespace ADS1115;

TEST(Threshold, create)
{
    Threshold thresh {};
    ASSERT_EQ(thresh.getHigh(), 32767);
    ASSERT_EQ(thresh.getLow(), -32768);

    thresh = Threshold(-16, 16);
    ASSERT_EQ(thresh.getHigh(), 16);
    ASSERT_EQ(thresh.getLow(), -16);

    thresh = Threshold(16, -16);
    ASSERT_EQ(thresh.getHigh(), -16);
    ASSERT_EQ(thresh.getLow(), 16);

    thresh = Threshold(15, 16);
    ASSERT_EQ(thresh.getHigh(), 16);
    ASSERT_EQ(thresh.getLow(), 15);

    ASSERT_THROW(Threshold(16, 15), std::runtime_error);
}

TEST(Threshold, set)
{
    Threshold thresh {};

    thresh.set(-16, 16);
    ASSERT_EQ(thresh.getHigh(), 16);
    ASSERT_EQ(thresh.getLow(), -16);

    thresh.set(16, -16);
    ASSERT_EQ(thresh.getHigh(), -16);
    ASSERT_EQ(thresh.getLow(), 16);

    thresh.set(15, 16);
    ASSERT_EQ(thresh.getHigh(), 16);
    ASSERT_EQ(thresh.getLow(), 15);

    ASSERT_THROW(thresh.set(16, 15), std::runtime_error);
}
