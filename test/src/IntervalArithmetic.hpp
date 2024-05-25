#ifndef INTERVALARITHMETIC_HPP_
#define INTERVALARITHMETIC_HPP_

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

// Constants for convenience
static constexpr double INF = std::numeric_limits<double>::infinity();
static constexpr double QUIET_NAN = std::numeric_limits<double>::quiet_NaN();

// Given [x1, x2] using interval arithmetic
//
// a + b*in
//
// where a = x1
// where b = x2 - x1
// where in is the new integral number (similar as i in complex numbers)
//
// a + b*in = (a + b) - b*in
class IntervalNumber {

// Algebraic structure: Ring

private:

    double m_a{0.0};
    double m_b{0.0};

    // If one of the bounds is not a number, the whole interval is not a number.
    void check() noexcept
    {
        if (std::isnan(m_a) || std::isnan(m_b))
        {
            m_a = std::numeric_limits<double>::quiet_NaN();
            m_b = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    IntervalNumber() noexcept :
        m_a{0.0}, m_b{0.0}
    {
        check();
    }

    IntervalNumber(double a) noexcept :
        m_a{a}, m_b{0.0}
    {
        check();
    }

    IntervalNumber(double a, double b) noexcept :
        m_a{a}, m_b{b}
    {
        check();
    }

    // Positive representation
    IntervalNumber positive() const noexcept
    {
        if (m_b < 0.0)
        {
            return IntervalNumber(m_a + m_b, -m_b);
        }

        return *this;
    }

    // Negative representation
    IntervalNumber negative() const noexcept
    {
        if (m_b > 0.0)
        {
            return IntervalNumber(m_a + m_b, -m_b);
        }

        return *this;
    }

    double getA() const noexcept
    {
        return m_a;
    }

    double getB() const noexcept
    {
        return m_b;
    }

    bool operator==(const IntervalNumber& other) const noexcept
    {
        auto first = positive();
        auto second = other.positive();

        return (first.getA() == second.getA()) && (first.getB() == second.getB());
    }

    bool operator!=(const IntervalNumber& other) const noexcept
    {
        auto first = positive();
        auto second = other.positive();

        return (first.getA() != second.getA()) || (first.getB() != second.getB());
    }

    IntervalNumber operator+(const IntervalNumber& other) const noexcept
    {
        auto first = positive();
        auto second = other.positive();

        auto a = first.getA() + second.getA();
        auto b = std::max(first.getB(), second.getB()) - a;

        return IntervalNumber(a, b);
    }

    IntervalNumber operator+(double x) const noexcept
    {
        return *this + IntervalNumber(x, x);
    }

    IntervalNumber operator*(const IntervalNumber& other) const noexcept
    {
        auto first = positive();
        auto second = other.positive();

        auto a = first.getA() * second.getA();
        auto b = std::max(getB(), other.getB());
        if (std::signbit(a))
        {
            b *= -1.0;
        }

        return IntervalNumber(a, b);
    }

    IntervalNumber operator*(double x) const noexcept
    {
        return *this * IntervalNumber(x, x);
    }

};

IntervalNumber operator+(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) + other;
}

IntervalNumber operator*(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) * other;
}

#endif /* INTERVALARITHMETIC_HPP_ */
