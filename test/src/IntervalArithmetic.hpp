#ifndef INTERVALARITHMETIC_HPP_
#define INTERVALARITHMETIC_HPP_

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#include "ComplexNumber.hpp"

// Constants for convenience
static constexpr double INF = std::numeric_limits<double>::infinity();
static constexpr double QUIET_NAN = std::numeric_limits<double>::quiet_NaN();

// Given [x0, x1] using interval arithmetic with complex numbers.
// For simplicity, only the four intervals in the illustration are supported.
class IntervalArithmetic {

// Algebraic structure: Ring

private:

    double m_x0{0.0};
    double m_x1{0.0};

    // If one of the bounds is not a number, the whole interval is not a number.
    void check() noexcept
    {
        if (std::isnan(m_x0) || std::isnan(m_x1))
        {
            m_x0 = std::numeric_limits<double>::quiet_NaN();
            m_x1 = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    IntervalArithmetic() noexcept :
        m_x0{0.0}, m_x1{0.0}
    {
        check();
    }

    IntervalArithmetic(double x0) noexcept :
        m_x0{x0}, m_x1{0.0}
    {
        check();
    }

    IntervalArithmetic(double x0, double x1) noexcept :
        m_x0{x0}, m_x1{x1}
    {
        check();
    }

    double getX0() const noexcept
    {
        return m_x0;
    }

    double getX1() const noexcept
    {
        return m_x1;
    }

    bool operator==(const IntervalArithmetic& other) const noexcept
    {
        return (getX0() == other.getX0()) && (getX1() == other.getX1());
    }

    bool operator!=(const IntervalArithmetic& other) const noexcept
    {
        return (getX0() != other.getX0()) || (getX1() != other.getX1());
    }

    IntervalArithmetic operator+(const IntervalArithmetic& other) const noexcept
    {
        ComplexNumber first{getX0(), getX1()};
        ComplexNumber second{other.getX0(), other.getX1()};

        auto result = first + second;

        return IntervalArithmetic(result.getA(), result.getB());
    }

    IntervalArithmetic operator+(double x) const noexcept
    {
        return *this + IntervalArithmetic(x, x);
    }

    IntervalArithmetic operator*(const IntervalArithmetic& other) const noexcept
    {
        ComplexNumber first{getX0(), getX1()};
        ComplexNumber second{other.getX0(), other.getX1()};

        auto result = first * second;

        return IntervalArithmetic(result.getA(), result.getB());
    }

    IntervalArithmetic operator*(double x) const noexcept
    {
        return *this * IntervalArithmetic(x, x);
    }

};

IntervalArithmetic operator+(double x, const IntervalArithmetic& other) noexcept
{
    return IntervalArithmetic(x) + other;
}

IntervalArithmetic operator*(double x, const IntervalArithmetic& other) noexcept
{
    return IntervalArithmetic(x) * other;
}

#endif /* INTERVALARITHMETIC_HPP_ */
