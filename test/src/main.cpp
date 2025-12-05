#include <cstdio>
#include <limits>

#include <gtest/gtest.h>

#include "IntervalNumber.hpp"

// Basic tests regarding numeric limits in C++.

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

// Tests for the interval number implementation.

TEST(IntervalNumber, ConstructorStandard01)
{
    IntervalNumber result{};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, ConstructorStandard02)
{
    IntervalNumber result{0.0, 10.0};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 10.0);
}

TEST(IntervalNumber, ConstructorZeroInfinity)
{
    IntervalNumber result{0.0, INF};

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, ConstructorNaN01)
{
    IntervalNumber result{0.0, QUIET_NAN};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(IntervalNumber, ConstructorNaN02)
{
    IntervalNumber result{QUIET_NAN, 0.0};

    EXPECT_EQ(true, std::isnan(result.getX0()));
    EXPECT_EQ(true, std::isnan(result.getX1()));
}

TEST(IntervalNumber, Multiplication01)
{
    IntervalNumber b{1.0};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -1.0);
    EXPECT_EQ(result.getX1(), -1.0);
}

TEST(IntervalNumber, Multiplication02)
{
    IntervalNumber b{INF};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(IntervalNumber, Multiplication03)
{
    IntervalNumber b{0.0, INF};

    auto result = -1.0 * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, Multiplication04)
{
    IntervalNumber a{2.0};
    IntervalNumber b{3.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 6.0);
    EXPECT_EQ(result.getX1(), 6.0);
}

TEST(IntervalNumber, Multiplication05)
{
    IntervalNumber a{0.0, INF};
    IntervalNumber b{0.0, INF};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Thesis01)
{
    IntervalNumber a{-1.0};
    IntervalNumber bc{-INF, 0.0};

    auto result = a * bc;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Thesis02)
{
    IntervalNumber a{-1.0};
    IntervalNumber b{0.0};
    IntervalNumber c{-INF};

    auto result = a * (b * c);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, MultiplicationNotAssociative)
{
    IntervalNumber a{-1.0};
    IntervalNumber b{0.0};
    IntervalNumber c{-INF};

    auto result_0 = a * (b * c);
    auto result_1 = (a * b) * c;

    EXPECT_NE(result_0, result_1);
}

// Additional tests for complete interval multiplication

TEST(IntervalNumber, MultiplicationNegativeIntervals)
{
    IntervalNumber a{-2.0, -1.0};
    IntervalNumber b{3.0, 4.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -8.0);
    EXPECT_EQ(result.getX1(), -3.0);
}

TEST(IntervalNumber, MultiplicationMixedSigns)
{
    IntervalNumber a{-2.0, 3.0};
    IntervalNumber b{-1.0, 4.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -8.0);
    EXPECT_EQ(result.getX1(), 12.0);
}

TEST(IntervalNumber, MultiplicationSpanningZero)
{
    IntervalNumber a{-3.0, 2.0};
    IntervalNumber b{-1.0, 1.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -3.0);
    EXPECT_EQ(result.getX1(), 3.0);
}

TEST(IntervalNumber, MultiplicationWithInfinityEndpoints)
{
    IntervalNumber a{-INF, -1.0};
    IntervalNumber b{2.0, 3.0};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -2.0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
