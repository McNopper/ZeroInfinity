#include <algorithm>
#include <cmath>
#include <cstdio>
#include <limits>
#include <stdexcept>
#include <vector>

// Interval operators see https://en.wikipedia.org/wiki/Interval_arithmetic
class Interval {

private:

    std::vector<double> m_bounds{0.0, 0.0};

public:

    Interval(double x) noexcept
    {
        m_bounds[0] = x;
        m_bounds[1] = x;
    }

    Interval(double bound0, double bound1) noexcept
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

    Interval operator+(const Interval& other) const noexcept
    {
        return Interval(lowerBound() + other.lowerBound(), upperBound() + other.upperBound());
    }

    Interval operator-(const Interval& other) const noexcept
    {
        return Interval(lowerBound() - other.upperBound(), upperBound() - other.lowerBound());
    }

    Interval operator*(const Interval& other) const noexcept
    {
        auto x1y1 = lowerBound() * other.lowerBound();
        auto x1y2 = lowerBound() * other.upperBound();
        auto x2y1 = upperBound() * other.lowerBound();
        auto x2y2 = upperBound() * other.upperBound();

        auto bound0 = std::min(x1y1, x1y2);
        bound0 = std::min(bound0, x2y1);
        bound0 = std::min(bound0, x2y2);

        auto bound1 = std::max(x1y1, x1y2);
        bound1 = std::max(bound0, x2y1);
        bound1 = std::max(bound0, x2y2);

        return Interval(bound0, bound1);
    }

    Interval operator/(const Interval& other) const
    {
        static constexpr auto INF = std::numeric_limits<double>::infinity();

        if (other.lowerBound() != 0.0 || other.upperBound() != 0.0)
        {
            if (other.lowerBound() < 0.0)
            {
                return *this * Interval(-INF, 1.0 / other.lowerBound());
            }
            else if (other.upperBound() > 0.0)
            {
                return *this * Interval(1.0 / other.upperBound(), INF);
            }

            return *this * Interval(1.0 / other.upperBound(), 1.0 / other.lowerBound());
        }

        return *this * Interval(-INF, INF);
    }

    Interval operator*(double x) const noexcept
    {
        return Interval(lowerBound() * x, upperBound() * x);
    }

    Interval operator/(double x) const
    {
        return Interval(lowerBound() / x, upperBound() / x);
    }

};

Interval operator*(double x, const Interval& other) noexcept
{
    return Interval(x * other.lowerBound(), x * other.upperBound());
}

Interval operator/(double x, const Interval& other)
{
    return Interval(x / other.lowerBound(), x / other.upperBound());
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
    auto c = Interval(0.0, inf);
    printf("[%lf, %lf]\n", c.lowerBound(), c.upperBound());

    // Checking the multiplication
    auto d = -1.0 * c;
    printf("[%lf, %lf]\n", d.lowerBound(), d.upperBound());

    return 0;
}
