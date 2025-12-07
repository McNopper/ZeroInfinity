#ifndef INTERVALNUMBER_HPP_
#define INTERVALNUMBER_HPP_

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <set>
#include <string>
#include <vector>

// Constants for convenience.
static constexpr double INF = std::numeric_limits<double>::infinity();
static constexpr double QUIET_NAN = std::numeric_limits<double>::quiet_NaN();

// Given interval [x0, x1] with extended real number system.
class IntervalNumber {

private:

    // x0 and x1 are stored in array.
    std::array<double, 2u> m_interval{0.0, 0.0};

    void check() noexcept
    {
        // Always guarantee, that m_x0 <= m_x1.
        if (m_interval[0u] > m_interval[1u])
        {
            auto x = m_interval[0u];
            m_interval[0u] = m_interval[1u];
            m_interval[1u] = x;
        }

        // If one of the bounds is not a number, the whole interval is not a number.
        if (std::isnan(m_interval[0u]) || std::isnan(m_interval[1u]))
        {
            m_interval[0u] = std::numeric_limits<double>::quiet_NaN();
            m_interval[1u] = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    IntervalNumber() noexcept
    {
        check();
    }

    IntervalNumber(double x0) noexcept :
        m_interval{x0, x0}
    {
        check();
    }

    IntervalNumber(double x0, double x1) noexcept :
        m_interval{x0, x1}
    {
        check();
    }

    double getX0() const noexcept
    {
        return m_interval[0u];
    }

    double getX1() const noexcept
    {
        return m_interval[1u];
    }

    std::string toString() const noexcept
    {
        return "[" + std::to_string(m_interval[0u]) + ", " + std::to_string(m_interval[1u]) + "]in";
    }

    bool operator==(const IntervalNumber& other) const noexcept
    {
        return (getX0() == other.getX0()) && (getX1() == other.getX1());
    }

    bool operator!=(const IntervalNumber& other) const noexcept
    {
        return (getX0() != other.getX0()) || (getX1() != other.getX1());
    }

    // Multiplication

    IntervalNumber operator*(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

        // Compute all four cross products as defined for interval multiplication.
        for (std::size_t l = 0u; l < 2u; l++)
        {
            for (std::size_t r = 0u; r < 2u; r++)
            {
                auto result = m_interval[l] * other.m_interval[r];
                if (!std::isnan(result))
                {
                    results.insert(result);
                }
                else
                {
                    // Check for indeterminate forms.
                    if ((m_interval[l] == -INF && other.m_interval[r] == 0.0) || (m_interval[l] == 0.0 && other.m_interval[r] == -INF))
                    {
                        results.insert(-INF);
                        results.insert(0.0);
                    }
                    if ((m_interval[l] == 0.0 && other.m_interval[r] == INF) || (m_interval[l] == INF && other.m_interval[r] == 0.0))
                    {
                        results.insert(0.0);
                        results.insert(INF);
                    }
                }
            }
        }

        // No results means not a number.
        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        // Set in C++ is ordered, so first and last results are the interval endpoints.
        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    IntervalNumber operator*(double x) const noexcept
    {
        return *this * IntervalNumber(x);
    }

    // Addition

    IntervalNumber operator+(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

        // Compute for interval addition.
        for (std::size_t i = 0u; i < 2u; i++)
        {
            auto result = m_interval[i] + other.m_interval[i];
            if (!std::isnan(result))
            {
                results.insert(result);
            }
            else
            {
                // Check for indeterminate forms.
                if ((m_interval[i] == -INF && other.m_interval[i] == INF) || (m_interval[i] == INF && other.m_interval[i] == -INF))
                {
                    results.insert(-INF);
                    results.insert(INF);
                }
            }
        }

        // No results means not a number.
        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        // Set in C++ is ordered, so first and last results are the interval endpoints.
        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    IntervalNumber operator+(double x) const noexcept
    {
        return *this + IntervalNumber(x);
    }

    // Subtraction

    IntervalNumber operator-(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

        // Compute for interval subtraction.
        for (std::size_t i = 0u; i < 2u; i++)
        {
            auto k = (i + 1u) % 2u;

            auto result = m_interval[i] - other.m_interval[k];
            if (!std::isnan(result))
            {
                results.insert(result);
            }
            else
            {
                // Check for indeterminate forms.
                if ((m_interval[i] == INF && other.m_interval[k] == INF) || (m_interval[i] == -INF && other.m_interval[k] == -INF))
                {
                    results.insert(-INF);
                    results.insert(INF);
                }
            }
        }

        // No results means not a number.
        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        // Set in C++ is ordered, so first and last results are the interval endpoints.
        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    IntervalNumber operator-(double x) const noexcept
    {
        return *this - IntervalNumber(x);
    }

};

IntervalNumber operator*(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) * other;
}

IntervalNumber operator+(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) + other;
}

IntervalNumber operator-(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) - other;
}

// ToDo: Implement division and absolute value operations for IntervalNumber, consistent with README definitions.

#endif /* INTERVALNUMBER_HPP_ */
