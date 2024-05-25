#include <cstdio>
#include <limits>

#include <gtest/gtest.h>

#include "IntervalNumber.hpp"

// Basic tests for the C++ implementation

TEST(Basics, ZeroMultiplyInfinity)
{
    double result = 0.0 * INF;

    EXPECT_EQ(true, std::isnan(result));
}

TEST(Basics, OnePlusInfinity)
{
    double result = 1.0 + INF;

    EXPECT_EQ(true, std::isinf(result));
}

TEST(Basics, MinusInfinityByInfinity)
{
    double result = -INF * INF;

    EXPECT_EQ(true, std::isinf(result));
}

TEST(Basics, InfinityMinusInfinity)
{
    double result = INF - INF;

    EXPECT_EQ(true, std::isnan(result));
}

// Tests for IntervalNumber implementation

TEST(IntervalNumber, ConstructorStandard01)
{
    IntervalNumber result;

    EXPECT_EQ(result.getA(), 0.0);
    EXPECT_EQ(result.getB(), 0.0);
}

TEST(IntervalNumber, ConstructorStandard02)
{
    // Creating the [1, 10] interval number
    IntervalNumber result{1.0, 9.0};

    EXPECT_EQ(result.getA(), 1.0);
    EXPECT_EQ(result.getB(), 9.0);
}

TEST(IntervalNumber, ConstructorZeroInfinity)
{
    // Creating the [0, ∞] interval number
    IntervalNumber result{0.0, INF};

    EXPECT_EQ(result.getA(), 0.0);
    EXPECT_EQ(result.getB(), INF);
}

TEST(IntervalNumber, Addition01)
{
    IntervalNumber a{0.0, 8.0};
    IntervalNumber b{1.0, 4.0};

    auto result = a + b;

    EXPECT_EQ(result.getA(), 1.0);
    EXPECT_EQ(result.getB(), 7.0);
}

TEST(IntervalNumber, Addition02)
{
    IntervalNumber a{0.0, INF};
    IntervalNumber b{0.0, INF};

    auto result = a + b;

    EXPECT_EQ(result.getA(), 0.0);
    EXPECT_EQ(result.getB(), INF);
}

TEST(IntervalNumber, Multiplication01)
{
    IntervalNumber a{1.0, 2.0};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getA(), -1.0);
    EXPECT_EQ(result.getB(), -2.0);
}


TEST(IntervalNumber, Multiplication02)
{
    IntervalNumber a{1.0, INF};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getA(), -1.0);
    EXPECT_EQ(result.getB(), -INF);
}

TEST(IntervalNumber, Multiplication03)
{
    IntervalNumber a{0.0, INF};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getA(), 0.0);
    EXPECT_EQ(result.getB(), -INF);
}

TEST(IntervalNumber, Multiplication04)
{
    IntervalNumber a{0.0, INF};
    IntervalNumber b{0.0, INF};

    auto result = a * b;

    EXPECT_EQ(result.getA(), 0.0);
    EXPECT_EQ(result.getB(), INF);
}

TEST(IntervalNumber, Multiplication05)
{
    IntervalNumber a{-INF, 0.0};
    IntervalNumber b{INF, 0.0};

    auto result = a * b;

    EXPECT_EQ(result.getA(), -INF);
    EXPECT_EQ(result.getB(), 0.0);
}

TEST(IntervalNumber, CheckNaN01)
{
    IntervalNumber result{0.0, QUIET_NAN};

    EXPECT_EQ(true, std::isnan(result.getA()));
    EXPECT_EQ(true, std::isnan(result.getB()));
}

TEST(IntervalNumber, CheckNaN02)
{
    IntervalNumber result{QUIET_NAN, 0.0};

    EXPECT_EQ(true, std::isnan(result.getA()));
    EXPECT_EQ(true, std::isnan(result.getB()));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
