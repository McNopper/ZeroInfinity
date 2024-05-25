#include <cstdio>
#include <limits>

#include <gtest/gtest.h>

#include "IntervalArithmetic.hpp"

// Constants for convenience

static constexpr double INF = std::numeric_limits<double>::infinity();
static constexpr double QUIET_NAN = std::numeric_limits<double>::quiet_NaN();

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

TEST(Basics, InfinityMinusInfinity)
{
    double result = INF - INF;

    EXPECT_EQ(true, std::isnan(result));
}

// Tests for IntervalArithmetic implementation

TEST(IntervalArithmetic, ConstructorStandard)
{
    IntervalArithmetic result{1.0, 10.0};

    EXPECT_EQ(result.lowerBound(), 1.0);
    EXPECT_EQ(result.upperBound(), 10.0);
}

TEST(IntervalArithmetic, ConstructorSwizzle)
{
    IntervalArithmetic result{10.0, 1.0};

    EXPECT_EQ(result.lowerBound(), 1.0);
    EXPECT_EQ(result.upperBound(), 10.0);
}

TEST(IntervalArithmetic, ConstructorZeroInfinity)
{
    // Creating the [0, ∞] interval
    IntervalArithmetic result{0.0, INF};

    EXPECT_EQ(result.lowerBound(), 0.0);
    EXPECT_EQ(result.upperBound(), INF);
}

TEST(IntervalArithmetic, Addition01)
{
    IntervalArithmetic a{0.0, INF};
    IntervalArithmetic b{1.0, INF};

    auto result = a + b;

    EXPECT_EQ(result.lowerBound(), 1.0);
    EXPECT_EQ(result.upperBound(), INF);
}

TEST(IntervalArithmetic, Addition02)
{
    IntervalArithmetic a{0.0, INF};
    IntervalArithmetic b{0.0, INF};

    auto result = a + b;

    EXPECT_EQ(result.lowerBound(), 0.0);
    EXPECT_EQ(result.upperBound(), INF);
}

TEST(IntervalArithmetic, Multiplication01)
{
    IntervalArithmetic temp{0.0, INF};

    auto result = -1.0 * temp;

    EXPECT_EQ(result.lowerBound(), -INF);
    EXPECT_EQ(result.upperBound(), 0.0);
}

TEST(IntervalArithmetic, Multiplication02)
{
    IntervalArithmetic temp{-INF, 0.0};

    auto result = -1.0 * temp;

    EXPECT_EQ(result.lowerBound(), 0.0);
    EXPECT_EQ(result.upperBound(), INF);
}

TEST(IntervalArithmetic, Multiplication03)
{
    IntervalArithmetic a{0.0, INF};
    IntervalArithmetic b{0.0, INF};

    auto result = a * b;

    EXPECT_EQ(result.lowerBound(), 0.0);
    EXPECT_EQ(result.upperBound(), INF);
}

/*TEST(IntervalArithmetic, Multiplication04)
{
    IntervalArithmetic a{-MY_INF, 0.0};
    IntervalArithmetic b{0.0, MY_INF};

    auto result = a * b;

    EXPECT_EQ(result.lowerBound(), -MY_INF);
    EXPECT_EQ(result.upperBound(), 0.0);
}*/

TEST(IntervalArithmetic, BoundsNaN)
{
    IntervalArithmetic result{0.0, QUIET_NAN};

    EXPECT_EQ(true, std::isnan(result.lowerBound()));
    EXPECT_EQ(true, std::isnan(result.upperBound()));
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
