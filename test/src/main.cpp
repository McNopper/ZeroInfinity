#include <cstdio>
#include <limits>

#include <gtest/gtest.h>

#include "Interval.hpp"

// Basic tests for the C++ implementation.

TEST(Basics, ZeroByInfinity)
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

// Tests for IntervalArithmetic implementation

TEST(Interval, ConstructorStandard01)
{
    Interval result{};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(Interval, ConstructorStandard02)
{
    Interval result{0.0, 10.0};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 10.0);
}

TEST(Interval, ConstructorZeroInfinity)
{
    Interval result{0.0, INF};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(Interval, ConstructorNaN01)
{
    Interval result{0.0, QUIET_NAN};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(Interval, ConstructorNaN02)
{
    Interval result{QUIET_NAN, 0.0};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(Interval, Addition01)
{
    Interval a{1.0, 1.0};
    Interval b{2.0, 2.0};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), 3.0);
    EXPECT_EQ(result.getX1(), 3.0);
}

TEST(Interval, Addition02)
{
    Interval a{0.0, INF};
    Interval b{0.0, INF};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(Interval, Multiplication01)
{
    Interval b{1.0};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -1.0);
    EXPECT_EQ(result.getX1(), -1.0);
}

TEST(Interval, Multiplication02)
{
    Interval b{INF};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(Interval, Multiplication03)
{
    Interval b{0.0, INF};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(Interval, Multiplication04)
{
    Interval a{2.0};
    Interval b{3.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 6.0);
    EXPECT_EQ(result.getX1(), 6.0);
}

TEST(Interval, Multiplication05)
{
    Interval a{0.0, INF};
    Interval b{0.0, INF};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(Interval, StatusQuo)
{
    Interval a{-1.0};
    Interval b{0.0};
    Interval c{-INF};

    auto result = a * (b * c);

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(Interval, Thesis)
{
    Interval a{-1.0};
    Interval bc{-INF, 0.0};

    auto result = a * bc;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
