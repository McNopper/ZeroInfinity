#ifndef INTERVALARITHMETIC_HPP_
#define INTERVALARITHMETIC_HPP_

#include <cmath>
#include <limits>
#include <vector>

// New interval arithmetic based on https://en.wikipedia.org/wiki/Interval_arithmetic
class IntervalArithmetic {

private:

    std::vector<double> m_bounds{0.0, 0.0};

    // If one of the bounds is not a number, the whole interval is not a number.
    void check() noexcept
    {
        if (std::isnan(m_bounds[0]) || std::isnan(m_bounds[1]))
        {
            m_bounds[0] = std::numeric_limits<double>::quiet_NaN();
            m_bounds[1] = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    IntervalArithmetic(double x) noexcept
    {
        m_bounds[0] = x;
        m_bounds[1] = x;

        check();
    }

    IntervalArithmetic(double bound0, double bound1) noexcept
    {
        if (bound0 < bound1)
        {
            m_bounds[0] = bound0;
            m_bounds[1] = bound1;
        }
        else
        {
            m_bounds[0] = bound1;
            m_bounds[1] = bound0;
        }

        check();
    }

    double lowerBound() const noexcept
    {
        return m_bounds[0];
    }

    double upperBound() const noexcept
    {
        return m_bounds[1];
    }

    bool operator==(const IntervalArithmetic& other) const noexcept
    {
        return (lowerBound() == other.lowerBound()) && (upperBound() == other.upperBound());
    }

    bool operator!=(const IntervalArithmetic& other) const noexcept
    {
        return (lowerBound() != other.lowerBound()) || (upperBound() != other.upperBound());
    }

    IntervalArithmetic operator+(const IntervalArithmetic& other) const noexcept
    {
        return IntervalArithmetic(lowerBound() + other.lowerBound(), upperBound() + other.upperBound());
    }

    IntervalArithmetic operator+(double x) const noexcept
    {
        return IntervalArithmetic(lowerBound() + x, upperBound() + x);
    }

    IntervalArithmetic operator-(const IntervalArithmetic& other) const noexcept
    {
        return IntervalArithmetic(lowerBound() - other.lowerBound(), upperBound() - other.upperBound());
    }

    IntervalArithmetic operator-(const double x) const noexcept
    {
        return IntervalArithmetic(lowerBound() - x, upperBound() - x);
    }

    IntervalArithmetic operator*(const IntervalArithmetic& other) const noexcept
    {
        return IntervalArithmetic(lowerBound() * other.lowerBound(), upperBound() * other.upperBound());
    }

    IntervalArithmetic operator*(double x) const noexcept
    {
        return IntervalArithmetic(lowerBound() * x, upperBound() * x);
    }

    IntervalArithmetic operator/(const IntervalArithmetic& other) const
    {
        return IntervalArithmetic(lowerBound() / other.lowerBound(), upperBound() / other.upperBound());
    }

    IntervalArithmetic operator/(double x) const
    {
        return IntervalArithmetic(lowerBound() / x, upperBound() / x);
    }

};

IntervalArithmetic operator+(double x, const IntervalArithmetic& other) noexcept
{
    return IntervalArithmetic(x + other.lowerBound(), x + other.upperBound());
}

IntervalArithmetic operator-(double x, const IntervalArithmetic& other) noexcept
{
    return IntervalArithmetic(x - other.lowerBound(), x - other.upperBound());
}

IntervalArithmetic operator*(double x, const IntervalArithmetic& other) noexcept
{
    return IntervalArithmetic(x * other.lowerBound(), x * other.upperBound());
}

IntervalArithmetic operator/(double x, const IntervalArithmetic& other)
{
    return IntervalArithmetic(x / other.lowerBound(), x / other.upperBound());
}

#endif /* INTERVALARITHMETIC_HPP_ */
