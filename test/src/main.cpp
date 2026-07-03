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

TEST(IntervalNumber, RuleI_ZeroTimesInfinity)
{
    // Rule I: 0 * ∞ = [0, ∞]in
    IntervalNumber a{0.0};
    IntervalNumber b{INF};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, RuleII_ZeroTimesNegativeInfinity)
{
    // Rule II: 0 * -∞ = [-∞, 0]in
    IntervalNumber a{0.0};
    IntervalNumber b{-INF};

    auto result = a * b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), 0.0);
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

// Additional tests for complete interval multiplication.

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

// Addition tests

TEST(IntervalNumber, Addition01)
{
    IntervalNumber a{1.0, 2.0};
    IntervalNumber b{3.0, 4.0};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 6.0);
}

TEST(IntervalNumber, Addition02)
{
    IntervalNumber a{-2.0, 3.0};
    IntervalNumber b{-1.0, 5.0};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), -3.0);
    EXPECT_EQ(result.getX1(), 8.0);
}

TEST(IntervalNumber, AdditionInfinity)
{
    IntervalNumber a{0.0, INF};
    IntervalNumber b{INF};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AdditionIndeterminateForm)
{
    // ∞ + -∞ = [-∞, ∞]in
    IntervalNumber a{INF};
    IntervalNumber b{-INF};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AdditionIndeterminateFormReverse)
{
    // -∞ + ∞ = [-∞, ∞]in
    IntervalNumber a{-INF};
    IntervalNumber b{INF};

    auto result = a + b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

// Subtraction tests

TEST(IntervalNumber, Subtraction01)
{
    IntervalNumber a{5.0, 8.0};
    IntervalNumber b{2.0, 3.0};

    auto result = a - b;

    EXPECT_EQ(result.getX0(), 2.0);
    EXPECT_EQ(result.getX1(), 6.0);
}

TEST(IntervalNumber, Subtraction02)
{
    IntervalNumber a{-2.0, 3.0};
    IntervalNumber b{-5.0, 1.0};

    auto result = a - b;

    EXPECT_EQ(result.getX0(), -3.0);
    EXPECT_EQ(result.getX1(), 8.0);
}

TEST(IntervalNumber, SubtractionIndeterminateForm)
{
    // ∞ - ∞ = [-∞, ∞]in
    IntervalNumber a{INF};
    IntervalNumber b{INF};

    auto result = a - b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, SubtractionMinusInfinity)
{
    // -∞ - (-∞) = [-∞, ∞]in
    IntervalNumber a{-INF};
    IntervalNumber b{-INF};

    auto result = a - b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

// Division tests

TEST(IntervalNumber, Division01)
{
    IntervalNumber a{6.0, 12.0};
    IntervalNumber b{2.0, 3.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), 2.0);
    EXPECT_EQ(result.getX1(), 6.0);
}

TEST(IntervalNumber, Division02)
{
    IntervalNumber a{-8.0, 4.0};
    IntervalNumber b{2.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -4.0);
    EXPECT_EQ(result.getX1(), 2.0);
}

TEST(IntervalNumber, DivisionByZeroIndeterminateForm)
{
    // 0/0 = [-∞, ∞]in
    IntervalNumber a{0.0};
    IntervalNumber b{0.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionInfinityByInfinity)
{
    // ∞/∞ = [0, ∞]in
    IntervalNumber a{INF};
    IntervalNumber b{INF};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByInfinity)
{
    IntervalNumber a{5.0, 10.0};
    IntervalNumber b{INF};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, DivisionNegativeIntervals)
{
    IntervalNumber a{-12.0, -6.0};
    IntervalNumber b{2.0, 3.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -6.0);
    EXPECT_EQ(result.getX1(), -2.0);
}

// Absolute value tests

TEST(IntervalNumber, AbsoluteValue01)
{
    IntervalNumber a{3.0, 5.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 3.0);
    EXPECT_EQ(result.getX1(), 5.0);
}

TEST(IntervalNumber, AbsoluteValue02)
{
    IntervalNumber a{-5.0, -3.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 3.0);
    EXPECT_EQ(result.getX1(), 5.0);
}

TEST(IntervalNumber, AbsoluteValue03)
{
    // Interval contains zero
    IntervalNumber a{-5.0, 3.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 5.0);
}

TEST(IntervalNumber, AbsoluteValue04)
{
    IntervalNumber a{-10.0, 15.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 15.0);
}

TEST(IntervalNumber, AbsoluteValueZero)
{
    IntervalNumber a{0.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, AbsoluteValueInfinity)
{
    IntervalNumber a{-INF, INF};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AbsoluteValueNegativeInfinity)
{
    IntervalNumber a{-INF, 0.0};

    auto result = abs(a);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

// Test examples from README

TEST(IntervalNumber, ReadmeExample01)
{
    // |0/0| + ∞ = ∞
    IntervalNumber zero_div_zero{-INF, INF};
    auto abs_result = abs(zero_div_zero);
    auto final_result = abs_result + INF;

    EXPECT_EQ(abs_result.getX0(), 0.0);
    EXPECT_EQ(abs_result.getX1(), INF);
    EXPECT_EQ(final_result.getX0(), INF);
    EXPECT_EQ(final_result.getX1(), INF);
}

TEST(IntervalNumber, ReadmeExample02)
{
    // (∞/∞) + ∞ = ∞
    IntervalNumber inf_div_inf{0.0, INF};
    auto result = inf_div_inf + INF;

    EXPECT_EQ(result.getX0(), INF);
    EXPECT_EQ(result.getX1(), INF);
}

// Additional edge case tests

TEST(IntervalNumber, DivisionIntervalContainingZero)
{
    // Division by interval containing zero should handle carefully
    IntervalNumber a{10.0, 20.0};
    IntervalNumber b{0.0, 2.0};
    
    auto result = a / b;
    
    // [10,20] / [0,2] = [10,20] * [1/2, 1/0] = [10,20] * [0.5, INF]
    EXPECT_EQ(result.getX0(), 5.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, MultiplicationZeroInterval)
{
    // [0,0] * anything = [0,0]
    IntervalNumber a{0.0};
    IntervalNumber b{-10.0, 10.0};
    
    auto result = a * b;
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, DivisionNegativeInfinity)
{
    // [-INF,-INF] / [2,3]
    IntervalNumber a{-INF};
    IntervalNumber b{2.0, 3.0};
    
    auto result = a / b;
    
    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(IntervalNumber, AdditionNegativeInfinity)
{
    // [-INF, -INF] + [1, 2]
    IntervalNumber a{-INF};
    IntervalNumber b{1.0, 2.0};
    
    auto result = a + b;
    
    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -INF);
}

TEST(IntervalNumber, SubtractionWithNegativeInfinity)
{
    // [1, 2] - [-INF, -INF]
    IntervalNumber a{1.0, 2.0};
    IntervalNumber b{-INF};
    
    auto result = a - b;
    
    EXPECT_EQ(result.getX0(), INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, MultiplicationBothNegativeInfinity)
{
    // [-INF, -1] * [-INF, -2]
    IntervalNumber a{-INF, -1.0};
    IntervalNumber b{-INF, -2.0};
    
    auto result = a * b;
    
    EXPECT_EQ(result.getX0(), 2.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByNegativeInfinity)
{
    // [10, 20] / [-INF, -INF]
    IntervalNumber a{10.0, 20.0};
    IntervalNumber b{-INF};
    
    auto result = a / b;
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 0.0);
}

TEST(IntervalNumber, NaNPropagation)
{
    // NaN should propagate through operations
    IntervalNumber a{QUIET_NAN};
    IntervalNumber b{5.0};
    
    auto result1 = a * b;
    auto result2 = a + b;
    auto result3 = a - b;
    auto result4 = a / b;
    
    EXPECT_TRUE(std::isnan(result1.getX0()));
    EXPECT_TRUE(std::isnan(result2.getX0()));
    EXPECT_TRUE(std::isnan(result3.getX0()));
    EXPECT_TRUE(std::isnan(result4.getX0()));
}

// Power operation tests

TEST(IntervalNumber, Power_IndeterminateForm_0_pow_0)
{
    // 0^0 = [0, ∞]in
    IntervalNumber a{0.0};
    IntervalNumber exp{0.0};
    
    auto result = a.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_1_pow_Infinity)
{
    // 1^∞ = [0, ∞]in
    IntervalNumber a{1.0};
    IntervalNumber exp{INF};
    
    auto result = a.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_Infinity_pow_0)
{
    // ∞^0 = [0, ∞]in
    IntervalNumber a{INF};
    IntervalNumber exp{0.0};
    
    auto result = a.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_BaseContainsZero_pow_0)
{
    // [0,1]^0 = [0, ∞]in (V^ at the (0,0) corner)
    IntervalNumber a{0.0, 1.0};
    auto result = a.pow(IntervalNumber{0.0});
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_BaseContainsPosInf_pow_0)
{
    // [1,∞]^0 = [0, ∞]in (V^ at the (+inf,0) corner)
    IntervalNumber a{1.0, INF};
    auto result = a.pow(IntervalNumber{0.0});
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_NegInfinity_pow_0)
{
    // [-∞,-∞]^0 = [0, ∞]in (formal V^ assignment for (-inf,0))
    IntervalNumber a{-INF};
    auto result = a.pow(IntervalNumber{0.0});
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IndeterminateForm_1_pow_NegInfinity)
{
    // 1^(-∞) = [0, ∞]in (signed variant per V^)
    IntervalNumber a{1.0};
    auto result = a.pow(IntervalNumber{-INF});
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_PositiveInteger)
{
    // [2, 3]^2 = [4, 9]
    IntervalNumber a{2.0, 3.0};
    
    auto result = a.pow(IntervalNumber(2.0));
    
    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_PositiveInteger_Negative)
{
    // [-3, -2]^2 = [4, 9]
    IntervalNumber a{-3.0, -2.0};
    
    auto result = a.pow(IntervalNumber(2.0));
    
    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_EvenExponent_SpanningZero)
{
    // [-2, 3]^2 = [0, 9] (even exponent)
    IntervalNumber a{-2.0, 3.0};
    
    auto result = a.pow(IntervalNumber(2.0));
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_OddExponent)
{
    // [2, 3]^3 = [8, 27]
    IntervalNumber a{2.0, 3.0};
    
    auto result = a.pow(IntervalNumber(3.0));
    
    EXPECT_EQ(result.getX0(), 8.0);
    EXPECT_EQ(result.getX1(), 27.0);
}

TEST(IntervalNumber, Power_FractionalExponent)
{
    // [4, 9]^0.5 = [2, 3] (square root)
    IntervalNumber a{4.0, 9.0};
    
    auto result = a.pow(IntervalNumber(0.5));
    
    EXPECT_DOUBLE_EQ(result.getX0(), 2.0);
    EXPECT_DOUBLE_EQ(result.getX1(), 3.0);
}

TEST(IntervalNumber, Power_NegativeExponent)
{
    // [2, 4]^-1 = [0.25, 0.5]
    IntervalNumber a{2.0, 4.0};
    
    auto result = a.pow(IntervalNumber(-1.0));
    
    EXPECT_DOUBLE_EQ(result.getX0(), 0.25);
    EXPECT_DOUBLE_EQ(result.getX1(), 0.5);
}

TEST(IntervalNumber, Power_ZeroExponent)
{
    // [5, 10]^0 = [1, 1]
    IntervalNumber a{5.0, 10.0};
    
    auto result = a.pow(IntervalNumber(0.0));
    
    EXPECT_EQ(result.getX0(), 1.0);
    EXPECT_EQ(result.getX1(), 1.0);
}

TEST(IntervalNumber, Power_LargeExponent)
{
    // [2, 2]^10 = [1024, 1024]
    IntervalNumber a{2.0};
    
    auto result = a.pow(IntervalNumber(10.0));
    
    EXPECT_DOUBLE_EQ(result.getX0(), 1024.0);
    EXPECT_DOUBLE_EQ(result.getX1(), 1024.0);
}

TEST(IntervalNumber, Power_GlobalFunction)
{
    // Test global pow function with scalar (converted to interval)
    IntervalNumber a{2.0, 3.0};
    
    auto result = pow(a, 2.0);
    
    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

// Interval to interval power tests

TEST(IntervalNumber, Power_IntervalToInterval_Simple)
{
    // [2, 3]^[2, 2] = [4, 9]
    IntervalNumber base{2.0, 3.0};
    IntervalNumber exp{2.0};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_IntervalToInterval_Range)
{
    // [2, 2]^[1, 3] = [2, 8]
    IntervalNumber base{2.0};
    IntervalNumber exp{1.0, 3.0};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 2.0);
    EXPECT_EQ(result.getX1(), 8.0);
}

TEST(IntervalNumber, Power_IntervalToInterval_BothRanges)
{
    // [2, 3]^[1, 2] should compute 2^1, 2^2, 3^1, 3^2 = 2, 4, 3, 9 -> [2, 9]
    IntervalNumber base{2.0, 3.0};
    IntervalNumber exp{1.0, 2.0};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 2.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_IntervalToInterval_Indeterminate_0_0)
{
    // [0,0]^[0,0] = [0, ∞]in
    IntervalNumber base{0.0};
    IntervalNumber exp{0.0};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IntervalToInterval_Indeterminate_1_Inf)
{
    // [1,1]^[∞,∞] = [0, ∞]in
    IntervalNumber base{1.0};
    IntervalNumber exp{INF};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IntervalToInterval_Indeterminate_Inf_0)
{
    // [∞,∞]^[0,0] = [0, ∞]in
    IntervalNumber base{INF};
    IntervalNumber exp{0.0};
    
    auto result = base.pow(exp);
    
    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, Power_IntervalToInterval_ContainsOne)
{
    // [0.5, 2]^[0.5, 1.5] should include 1^anything = 1
    IntervalNumber base{0.5, 2.0};
    IntervalNumber exp{0.5, 1.5};
    
    auto result = base.pow(exp);
    
    // Result should contain 1 and range from min to max of all combinations
    EXPECT_LE(result.getX0(), 1.0);
    EXPECT_GE(result.getX1(), 1.0);
}

TEST(IntervalNumber, Power_IntervalToInterval_GlobalFunction)
{
    // Test global pow function with interval exponent
    IntervalNumber base{2.0, 3.0};
    IntervalNumber exp{2.0};
    
    auto result = pow(base, exp);
    
    EXPECT_EQ(result.getX0(), 4.0);
    EXPECT_EQ(result.getX1(), 9.0);
}

TEST(IntervalNumber, Power_IntervalToInterval_NegativeExponent)
{
    // [2, 4]^[-1, -1] = [0.25, 0.5]
    IntervalNumber base{2.0, 4.0};
    IntervalNumber exp{-1.0};
    
    auto result = base.pow(exp);
    
    EXPECT_DOUBLE_EQ(result.getX0(), 0.25);
    EXPECT_DOUBLE_EQ(result.getX1(), 0.5);
}

TEST(IntervalNumber, Power_IntervalToInterval_FractionalExponents)
{
    // [4, 9]^[0.5, 0.5] = [2, 3]
    IntervalNumber base{4.0, 9.0};
    IntervalNumber exp{0.5};
    
    auto result = base.pow(exp);
    
    EXPECT_DOUBLE_EQ(result.getX0(), 2.0);
    EXPECT_DOUBLE_EQ(result.getX1(), 3.0);
}

// =====================================================================
// Regression tests for fixes to reciprocal / division / abs / power.
// These cover correctness gaps identified during the scientific review
// of the paper.
// =====================================================================

TEST(IntervalNumber, ReciprocalOfZeroSpanningInterval)
{
    // 1 / [-1, 1]: divisor strictly contains zero, true reciprocal is
    // (-inf, -1] U [1, inf); the convex hull is [-inf, inf].
    IntervalNumber a{1.0};
    IntervalNumber b{-1.0, 1.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByZeroSpanningInterval_NumeratorPositive)
{
    // [2, 2] / [-1, 1] should be [-inf, inf], not [-2, 2].
    IntervalNumber a{2.0};
    IntervalNumber b{-1.0, 1.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByZeroSpanningInterval_AsymmetricSpan)
{
    // [1, 1] / [-2, 3]: divisor strictly contains zero -> hull [-inf, inf].
    IntervalNumber a{1.0};
    IntervalNumber b{-2.0, 3.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByLeftZeroBoundary)
{
    // [1, 1] / [-2, 0]: divisor approaches zero from the negative side.
    // Reciprocal is [-inf, -0.5], so result is [-inf, -0.5].
    IntervalNumber a{1.0};
    IntervalNumber b{-2.0, 0.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), -0.5);
}

TEST(IntervalNumber, DivisionByPointZero_NonZeroNumerator)
{
    // x / [0, 0] for x != 0: division is total on \mathcal{I}; result is the
    // full hull [-inf, inf] (paper §4.5).
    IntervalNumber a{5.0};
    IntervalNumber b{0.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, DivisionByPointZero_NegativeNumerator)
{
    IntervalNumber a{-3.0};
    IntervalNumber b{0.0};

    auto result = a / b;

    EXPECT_EQ(result.getX0(), -INF);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AbsoluteValueOfPositiveInfinityInterval)
{
    // |[0, +inf]| = [0, +inf]. Order-based definition must avoid 0*inf = NaN.
    IntervalNumber a{0.0, INF};

    auto result = a.abs();

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AbsoluteValueOfNegativeInfinityInterval)
{
    // |[-inf, 0]| = [0, +inf].
    IntervalNumber a{-INF, 0.0};

    auto result = a.abs();

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AbsoluteValueOfFullExtendedInterval)
{
    // |[-inf, +inf]| = [0, +inf].
    IntervalNumber a{-INF, INF};

    auto result = a.abs();

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), INF);
}

TEST(IntervalNumber, AbsoluteValuePreservesOrderForAsymmetricSpan)
{
    // |[-1, 5]| = [0, 5] (largest of |x0|, |x1| is 5).
    IntervalNumber a{-1.0, 5.0};

    auto result = a.abs();

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 5.0);

    // |[-7, 3]| = [0, 7].
    IntervalNumber b{-7.0, 3.0};

    auto result_b = b.abs();

    EXPECT_EQ(result_b.getX0(), 0.0);
    EXPECT_EQ(result_b.getX1(), 7.0);
}

TEST(IntervalNumber, PowerNegativeBaseNonIntegerExponent_ReturnsNaN)
{
    // (-2)^0.5 is not real-valued; power must signal partiality with NaN
    // rather than silently producing a misleading interval.
    IntervalNumber base{-2.0};
    IntervalNumber exp{0.5};

    auto result = base.pow(exp);

    EXPECT_TRUE(std::isnan(result.getX0()));
    EXPECT_TRUE(std::isnan(result.getX1()));
}

TEST(IntervalNumber, PowerSpanningZeroBaseNonIntegerExponent_ReturnsNaN)
{
    // [-1, 4]^0.5: lower corner (-1)^0.5 is not real -> NaN.
    IntervalNumber base{-1.0, 4.0};
    IntervalNumber exp{0.5};

    auto result = base.pow(exp);

    EXPECT_TRUE(std::isnan(result.getX0()));
    EXPECT_TRUE(std::isnan(result.getX1()));
}

// ---------------------------------------------------------------------
// Inclusion monotonicity (paper Prop. 5.3 + Remark 5.4).
// Monotonicity holds for +, -, *, |.| and exponentiation, but FAILS for
// the reciprocal / division at the degenerate divisor [0,0]: a narrower
// divisor ([0,0]) yields a wider reciprocal than a wider one-sided
// divisor ([0,2] / [-2,0]). These tests pin that documented exception.
// ---------------------------------------------------------------------

TEST(IntervalNumber, MonotonicityHoldsForMultiplication)
{
    // [1,1] subset [0,2] and [INF,INF] subset [1,INF]; products stay nested.
    auto small = IntervalNumber(1.0) * IntervalNumber(INF);          // [INF,INF]
    auto big   = IntervalNumber(0.0, 2.0) * IntervalNumber(1.0, INF); // [0,INF]
    EXPECT_TRUE(big.getX0() <= small.getX0() && small.getX1() <= big.getX1());
}

TEST(IntervalNumber, MonotonicityFailsForReciprocalAtPointZero)
{
    // [0,0] subset [0,2], yet 1/[0,0] = [-INF,INF] is NOT a subset of
    // 1/[0,2] = [0.5, INF].  (paper Remark 5.4)
    auto recipPointZero = IntervalNumber(1.0) / IntervalNumber(0.0);       // [-INF, INF]
    auto recipOneSided  = IntervalNumber(1.0) / IntervalNumber(0.0, 2.0);  // [0.5, INF]

    EXPECT_EQ(recipPointZero.getX0(), -INF);
    EXPECT_EQ(recipPointZero.getX1(), INF);
    EXPECT_EQ(recipOneSided.getX0(), 0.5);
    EXPECT_EQ(recipOneSided.getX1(), INF);

    // The wider divisor produces the narrower reciprocal: monotonicity fails.
    const bool isSubset =
        (recipOneSided.getX0() <= recipPointZero.getX0()) &&
        (recipPointZero.getX1() <= recipOneSided.getX1());
    EXPECT_FALSE(isSubset);
}

TEST(IntervalNumber, MonotonicityFailsForReciprocalAtPointZeroNegativeSide)
{
    // [0,0] subset [-2,0], yet 1/[0,0] = [-INF,INF] is NOT a subset of
    // 1/[-2,0] = [-INF, -0.5].  (paper Remark 5.4)
    auto recipPointZero = IntervalNumber(1.0) / IntervalNumber(0.0);        // [-INF, INF]
    auto recipOneSided  = IntervalNumber(1.0) / IntervalNumber(-2.0, 0.0);  // [-INF, -0.5]

    EXPECT_EQ(recipOneSided.getX0(), -INF);
    EXPECT_EQ(recipOneSided.getX1(), -0.5);

    const bool isSubset =
        (recipOneSided.getX0() <= recipPointZero.getX0()) &&
        (recipPointZero.getX1() <= recipOneSided.getX1());
    EXPECT_FALSE(isSubset);
}

// ---------------------------------------------------------------------
// Admissible-domain gating for exponentiation (paper Def. 4.7).
// Inputs outside the admissible domain are mathematically undefined and
// must return NaN rather than a fabricated interval.
// ---------------------------------------------------------------------

TEST(IntervalNumber, PowerNonAdmissible_NegativeIntegerExponent_ZeroSpanningBase_ReturnsNaN)
{
    // [-1, 4]^(-2): exponent is a negative integer but 0 in base, so case (iv)
    // does not apply and the pair is non-admissible -> NaN.
    IntervalNumber base{-1.0, 4.0};
    IntervalNumber exp{-2.0};

    auto result = base.pow(exp);

    EXPECT_TRUE(std::isnan(result.getX0()));
    EXPECT_TRUE(std::isnan(result.getX1()));
}

TEST(IntervalNumber, PowerNonAdmissible_NegativeExponentInterval_ZeroBase_ReturnsNaN)
{
    // [0, 2]^[-1, 1]: reaches 0^y with y < 0; non-admissible -> NaN.
    IntervalNumber base{0.0, 2.0};
    IntervalNumber exp{-1.0, 1.0};

    auto result = base.pow(exp);

    EXPECT_TRUE(std::isnan(result.getX0()));
    EXPECT_TRUE(std::isnan(result.getX1()));
}

TEST(IntervalNumber, PowerAdmissible_NonNegativeBase_NonNegativeExponentInterval)
{
    // [0, 2]^[1, 3] is admissible (case ii); no indeterminate corner is
    // reached, so the result is the plain image hull [0, 8].
    IntervalNumber base{0.0, 2.0};
    IntervalNumber exp{1.0, 3.0};

    auto result = base.pow(exp);

    EXPECT_EQ(result.getX0(), 0.0);
    EXPECT_EQ(result.getX1(), 8.0);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
