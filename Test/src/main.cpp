#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <vector>

// New interval arithmetic based on https://en.wikipedia.org/wiki/Interval_arithmetic
class IntervalArithmetic {

private:

    std::vector<double> m_bounds{0.0, 0.0};

public:

    IntervalArithmetic(double x) noexcept
    {
        m_bounds[0] = x;
        m_bounds[1] = x;
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
    }

    double lowerBound() const noexcept
    {
        return m_bounds[0];
    }

    double upperBound() const noexcept
    {
        return m_bounds[1];
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

int main(int argc, const char* argv[])
{
    // Using infinty as a constant
    constexpr auto inf = std::numeric_limits<double>::infinity();

    // Checking the lower interval bound
    auto a = 0.0 * 0.0;
    printf("0.0 * 0.0 = %lf\n", a);

    // Checking the upper interval bound
    auto b = inf * 1.0;
    printf("inf * 1.0 = %lf\n", b);

    // Creating the [0, ∞] interval
    auto c = IntervalArithmetic(0.0, inf);
    printf("[%lf, %lf]\n", c.lowerBound(), c.upperBound());

    // Checking the multiplication
    auto d = -1.0 * c;
    printf("[%lf, %lf]\n", d.lowerBound(), d.upperBound());

    return 0;
}
