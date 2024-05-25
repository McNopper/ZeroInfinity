#include <cstdio>
#include <limits>

#include <gtest/gtest.h>

#include "IntervalArithmetic.hpp"

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

// Tests for IntervalArithmetic implementation

TEST(IntervalArithmetic, ConstructorStandard01)
{
    IntervalArithmetic result;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalArithmetic, ConstructorStandard02)
{
    // Creating the [0, 10] interval
    IntervalArithmetic result{0.0, 10.0};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 10.0);
}

TEST(IntervalArithmetic, ConstructorZeroInfinity)
{
    // Creating the [0, ∞] interval
    IntervalArithmetic result{0.0, INF};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalArithmetic, ConstructorNaN01)
{
    IntervalArithmetic result{0.0, QUIET_NAN};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(IntervalArithmetic, ConstructorNaN02)
{
    IntervalArithmetic result{QUIET_NAN, 0.0};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(IntervalArithmetic, Addition01)
{
    IntervalArithmetic a{1.0, 0.0};
    IntervalArithmetic b{2.0, 0.0};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), 3.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalArithmetic, Addition02)
{
    IntervalArithmetic a{INF, 0.0};
    IntervalArithmetic b{INF, 0.0};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), INF);
    EXPECT_EQ(result.getX1(), 0.0);
}

/*
TEST(IntervalArithmetic, Multiplication01)
{
    IntervalArithmetic a{1.0, 2.0};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getX0(), -1.0);
    EXPECT_EQ(result.getX1(), -2.0);
}


TEST(IntervalArithmetic, Multiplication02)
{
    IntervalArithmetic a{1.0, INF};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getX0(), -1.0);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(IntervalArithmetic, Multiplication03)
{
    IntervalArithmetic a{0.0, INF};

    auto result = -1.0 * a;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(IntervalArithmetic, Multiplication04)
{
    IntervalArithmetic a{0.0, INF};
    IntervalArithmetic b{0.0, INF};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalArithmetic, Multiplication05)
{
    IntervalArithmetic a{-INF, 0.0};
    IntervalArithmetic b{INF, 0.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), 0.0);
}*/

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
