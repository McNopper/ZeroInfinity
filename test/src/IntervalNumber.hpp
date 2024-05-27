#ifndef INTERVALNUMBER_HPP_
#define INTERVALNUMBER_HPP_

#include <algorithm>
#include <cmath>
#include <limits>
#include <string>
#include <vector>

// Constants for convenience.
static constexpr double INF = std::numeric_limits<double>::infinity();
static constexpr double QUIET_NAN = std::numeric_limits<double>::quiet_NaN();

// Given interval [x0, x1] with extended real number system.
//
// Algebraic structure: Ring.
class IntervalNumber {

private:

    double m_x0{0.0};
    double m_x1{0.0};

    void check() noexcept
    {
        // Always guarantee, that m_x0 <= m_x1.
        if (m_x0 > m_x1)
        {
            auto x0 = m_x0;
            m_x0 = m_x1;
            m_x1 = x0;
        }

        // If one of the bounds is not a number, the whole interval is not a number.
        if (std::isnan(m_x0) || std::isnan(m_x1))
        {
            m_x0 = std::numeric_limits<double>::quiet_NaN();
            m_x1 = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    IntervalNumber() noexcept :
        m_x0{0.0}, m_x1{0.0}
    {
        check();
    }

    IntervalNumber(double x0) noexcept :
        m_x0{x0}, m_x1{x0}
    {
        check();
    }

    IntervalNumber(double x0, double x1) noexcept :
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

    std::string toString() const noexcept
    {
        return "[" + std::to_string(m_x0) + ", " + std::to_string(m_x1) + "]in";
    }

    bool operator==(const IntervalNumber& other) const noexcept
    {
        return (getX0() == other.getX0()) && (getX1() == other.getX1());
    }

    bool operator!=(const IntervalNumber& other) const noexcept
    {
        return (getX0() != other.getX0()) || (getX1() != other.getX1());
    }

    IntervalNumber operator+(const IntervalNumber& other) const noexcept
    {
        auto x0 = getX0() + other.getX0();
        auto x1 = getX1() + other.getX1();

        return IntervalNumber(x0, x1);
    }

    IntervalNumber operator+(double x) const noexcept
    {
        return *this + IntervalNumber(x);
    }

    IntervalNumber operator*(const IntervalNumber& other) const noexcept
    {
        auto x0 = getX0() * other.getX0();
        auto x1 = getX1() * other.getX1();

        return IntervalNumber(x0, x1);
    }

    IntervalNumber operator*(double x) const noexcept
    {
        return *this * IntervalNumber(x);
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

#endif /* INTERVALNUMBER_HPP_ */
