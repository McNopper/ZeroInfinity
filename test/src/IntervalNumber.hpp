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

/**
 * Represents an interval number [x0, x1]in using extended real numbers.
 * 
 * This class implements interval arithmetic for handling indeterminate forms
 * such as 0*∞, 0/0, ∞-∞, etc. according to the mathematical definitions
 * in the ZeroInfinity paper.
 */
class IntervalNumber {

private:

    // Internal storage for interval endpoints [x0, x1]
    std::array<double, 2u> m_interval{0.0, 0.0};

    /**
     * Validates and normalizes the interval to ensure x0 <= x1.
     * If either bound is NaN, the entire interval becomes NaN.
     */
    void check() noexcept
    {
        if (m_interval[0u] > m_interval[1u])
        {
            auto x = m_interval[0u];
            m_interval[0u] = m_interval[1u];
            m_interval[1u] = x;
        }

        if (std::isnan(m_interval[0u]) || std::isnan(m_interval[1u]))
        {
            m_interval[0u] = std::numeric_limits<double>::quiet_NaN();
            m_interval[1u] = std::numeric_limits<double>::quiet_NaN();
        }
    }

public:

    /**
     * Default constructor.
     * Initializes interval to [0, 0]in.
     */
    IntervalNumber() noexcept
    {
        check();
    }

    /**
     * Single value constructor.
     * Creates a point interval [x0, x0]in.
     * 
     * @param x0 The single value for both endpoints
     */
    IntervalNumber(double x0) noexcept :
        m_interval{x0, x0}
    {
        check();
    }

    /**
     * Interval constructor.
     * Creates an interval [x0, x1]in. Automatically ensures x0 <= x1.
     * 
     * @param x0 Lower bound
     * @param x1 Upper bound
     */
    IntervalNumber(double x0, double x1) noexcept :
        m_interval{x0, x1}
    {
        check();
    }

    /**
     * Gets the lower bound of the interval.
     * 
     * @return The value x0
     */
    double getX0() const noexcept
    {
        return m_interval[0u];
    }

    /**
     * Gets the upper bound of the interval.
     * 
     * @return The value x1
     */
    double getX1() const noexcept
    {
        return m_interval[1u];
    }

    /**
     * Converts the interval to a string representation.
     * 
     * @return String in format "[x0, x1]in"
     */
    std::string toString() const noexcept
    {
        return "[" + std::to_string(m_interval[0u]) + ", " + std::to_string(m_interval[1u]) + "]in";
    }

    /**
     * Equality operator.
     * Two intervals are equal if both endpoints match exactly.
     * 
     * @param other The interval to compare with
     * @return true if intervals are equal, false otherwise
     */
    bool operator==(const IntervalNumber& other) const noexcept
    {
        return (getX0() == other.getX0()) && (getX1() == other.getX1());
    }

    /**
     * Inequality operator.
     * 
     * @param other The interval to compare with
     * @return true if intervals are not equal, false otherwise
     */
    bool operator!=(const IntervalNumber& other) const noexcept
    {
        return (getX0() != other.getX0()) || (getX1() != other.getX1());
    }

    /**
     * Interval multiplication: [x0,x1]in * [y0,y1]in
     * 
     * Computes [min(x0*y0, x0*y1, x1*y0, x1*y1), max(x0*y0, x0*y1, x1*y0, x1*y1)]in
     * Handles indeterminate forms:
     *   - 0 * ∞ = [0, ∞]in (Rule I)
     *   - 0 * -∞ = [-∞, 0]in (Rule II)
     */
    IntervalNumber operator*(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

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

        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    /**
     * Scalar multiplication operator.
     * Multiplies interval by a scalar value.
     * 
     * @param x Scalar value
     * @return Resulting interval
     */
    IntervalNumber operator*(double x) const noexcept
    {
        return *this * IntervalNumber(x);
    }

    /**
     * Interval addition: [x0,x1]in + [y0,y1]in = [x0+y0, x1+y1]in
     * 
     * Handles indeterminate form:
     *   - ∞ + (-∞) = [-∞, ∞]in
     * 
     * @param other The interval to add
     * @return Resulting interval
     */
    IntervalNumber operator+(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

        for (std::size_t i = 0u; i < 2u; i++)
        {
            auto result = m_interval[i] + other.m_interval[i];
            if (!std::isnan(result))
            {
                results.insert(result);
            }
            else
            {
                if ((m_interval[i] == -INF && other.m_interval[i] == INF) || (m_interval[i] == INF && other.m_interval[i] == -INF))
                {
                    results.insert(-INF);
                    results.insert(INF);
                }
            }
        }

        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    /**
     * Scalar addition operator.
     * Adds a scalar value to the interval.
     * 
     * @param x Scalar value
     * @return Resulting interval
     */
    IntervalNumber operator+(double x) const noexcept
    {
        return *this + IntervalNumber(x);
    }

    /**
     * Interval subtraction: [x0,x1]in - [y0,y1]in = [x0-y1, x1-y0]in
     * 
     * Handles indeterminate forms:
     *   - ∞ - ∞ = [-∞, ∞]in
     *   - (-∞) - (-∞) = [-∞, ∞]in
     * 
     * @param other The interval to subtract
     * @return Resulting interval
     */
    IntervalNumber operator-(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

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
                if ((m_interval[i] == INF && other.m_interval[k] == INF) || (m_interval[i] == -INF && other.m_interval[k] == -INF))
                {
                    results.insert(-INF);
                    results.insert(INF);
                }
            }
        }

        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    /**
     * Scalar subtraction operator.
     * Subtracts a scalar value from the interval.
     * 
     * @param x Scalar value
     * @return Resulting interval
     */
    IntervalNumber operator-(double x) const noexcept
    {
        return *this - IntervalNumber(x);
    }

    /**
     * Interval division: [x0,x1]in / [y0,y1]in := [x0,x1]in * [1/y1, 1/y0]in
     * 
     * Handles indeterminate forms:
     *   - 0/0 = [-∞, ∞]in
     *   - ∞/∞ = [0, ∞]in
     * 
     * @param other The interval to divide by
     * @return Resulting interval
     */
    IntervalNumber operator/(const IntervalNumber& other) const noexcept
    {
        std::set<double> results{};

        std::array<double, 2u> reciprocal{0.0, 0.0};
        
        if (other.m_interval[0u] == 0.0 && other.m_interval[1u] == 0.0)
        {
            if (m_interval[0u] == 0.0 && m_interval[1u] == 0.0)
            {
                return IntervalNumber(-INF, INF);
            }
            return IntervalNumber(QUIET_NAN);
        }

        reciprocal[0u] = 1.0 / other.m_interval[1u];
        reciprocal[1u] = 1.0 / other.m_interval[0u];

        for (std::size_t l = 0u; l < 2u; l++)
        {
            for (std::size_t r = 0u; r < 2u; r++)
            {
                auto result = m_interval[l] * reciprocal[r];
                if (!std::isnan(result))
                {
                    results.insert(result);
                }
                else
                {
                    if ((m_interval[l] == -INF && reciprocal[r] == 0.0) || (m_interval[l] == 0.0 && reciprocal[r] == -INF))
                    {
                        results.insert(-INF);
                        results.insert(0.0);
                    }
                    if ((m_interval[l] == 0.0 && reciprocal[r] == INF) || (m_interval[l] == INF && reciprocal[r] == 0.0))
                    {
                        results.insert(0.0);
                        results.insert(INF);
                    }
                }
            }
        }

        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        return IntervalNumber(*results.begin(), *results.rbegin());
    }

    /**
     * Scalar division operator.
     * Divides the interval by a scalar value.
     * 
     * @param x Scalar value
     * @return Resulting interval
     */
    IntervalNumber operator/(double x) const noexcept
    {
        return *this / IntervalNumber(x);
    }

    /**
     * Absolute value of interval:
     *   |[x0,x1]|in = [min(|x0|,|x1|), max(|x0|,|x1|)]in if x0*x1 >= 0
     *   |[x0,x1]|in = [0, max(|x0|,|x1|)]in if x0*x1 < 0
     * 
     * @return Absolute value as interval
     */
    IntervalNumber abs() const noexcept
    {
        if (m_interval[0u] * m_interval[1u] >= 0.0)
        {
            double abs0 = std::fabs(m_interval[0u]);
            double abs1 = std::fabs(m_interval[1u]);
            return IntervalNumber(std::min(abs0, abs1), std::max(abs0, abs1));
        }
        else
        {
            double abs0 = std::fabs(m_interval[0u]);
            double abs1 = std::fabs(m_interval[1u]);
            return IntervalNumber(0.0, std::max(abs0, abs1));
        }
    }

    /**
     * Power operation: [x0,x1]in ^ [y0,y1]in
     * 
     * Computes interval raised to an interval power.
     * The result is the union of all possible powers: base^exp for all base in [x0,x1], exp in [y0,y1]
     * 
     * Handles indeterminate forms:
     *   - [0,0]^[0,0] = [0, ∞]in
     *   - [1,1]^[∞,∞] = [0, ∞]in
     *   - [∞,∞]^[0,0] = [0, ∞]in
     * 
     * General approach: compute base^exp for all combinations of interval endpoints.
     * Scalar exponents are automatically converted to single-point intervals.
     */
    IntervalNumber pow(const IntervalNumber& exponent) const noexcept
    {
        std::set<double> results{};

        // Handle indeterminate form: [0,0]^[0,0] = [0, ∞]in
        if (m_interval[0u] == 0.0 && m_interval[1u] == 0.0 &&
            exponent.m_interval[0u] == 0.0 && exponent.m_interval[1u] == 0.0)
        {
            return IntervalNumber(0.0, INF);
        }

        // Handle indeterminate form: [1,1]^[∞,∞] = [0, ∞]in
        if (m_interval[0u] == 1.0 && m_interval[1u] == 1.0 &&
            exponent.m_interval[0u] == INF && exponent.m_interval[1u] == INF)
        {
            return IntervalNumber(0.0, INF);
        }

        // Handle indeterminate form: [∞,∞]^[0,0] = [0, ∞]in
        if (m_interval[0u] == INF && m_interval[1u] == INF &&
            exponent.m_interval[0u] == 0.0 && exponent.m_interval[1u] == 0.0)
        {
            return IntervalNumber(0.0, INF);
        }

        // Compute all four combinations: base^exp for each endpoint pair
        for (std::size_t i = 0u; i < 2u; i++)
        {
            for (std::size_t j = 0u; j < 2u; j++)
            {
                double base = m_interval[i];
                double exp = exponent.m_interval[j];
                double result = std::pow(base, exp);
                
                if (!std::isnan(result) && !std::isinf(result))
                {
                    results.insert(result);
                }
                else if (std::isinf(result))
                {
                    results.insert(result);
                }
                else
                {
                    // Handle special NaN cases
                    if (base == 0.0 && exp == 0.0)
                    {
                        // 0^0 contributes to [0,∞] range
                        results.insert(0.0);
                        results.insert(INF);
                    }
                    else if (base == 1.0 && std::isinf(exp))
                    {
                        // 1^∞ contributes to [0,∞] range
                        results.insert(0.0);
                        results.insert(INF);
                    }
                    else if (std::isinf(base) && exp == 0.0)
                    {
                        // ∞^0 contributes to [0,∞] range
                        results.insert(0.0);
                        results.insert(INF);
                    }
                    else if (base == 0.0 && exp < 0.0)
                    {
                        // 0^negative = infinity
                        results.insert(INF);
                    }
                    else if (base < 0.0 && std::floor(exp) != exp)
                    {
                        // Negative base with non-integer exponent is undefined
                        continue;
                    }
                }
            }
        }

        // For intervals containing special cases, check intermediate values
        if (m_interval[0u] <= 1.0 && m_interval[1u] >= 1.0 && 
            exponent.m_interval[0u] <= 0.0 && exponent.m_interval[1u] >= 0.0)
        {
            // Interval contains 1^0 = 1
            results.insert(1.0);
        }

        // Handle even exponent intervals and negative bases
        if (m_interval[0u] < 0.0 && m_interval[1u] > 0.0)
        {
            // Base interval spans zero
            double minExp = exponent.m_interval[0u];
            double maxExp = exponent.m_interval[1u];
            
            if (minExp < 0.0 && maxExp < 0.0)
            {
                // All negative exponents with zero in base -> infinite result
                results.insert(-INF);
                results.insert(INF);
            }
            else if (minExp <= 0.0 && maxExp >= 0.0)
            {
                // Exponent spans zero, base spans zero -> can get any value
                results.insert(0.0);
                results.insert(INF);
            }
            else if (minExp == maxExp && std::floor(minExp) == minExp && static_cast<int>(minExp) % 2 == 0)
            {
                // Even integer exponent with base spanning zero: result includes 0
                results.insert(0.0);
            }
        }

        if (results.empty())
        {
            return IntervalNumber(QUIET_NAN);
        }

        return IntervalNumber(*results.begin(), *results.rbegin());
    }

};

/**
 * Global multiplication operator (scalar * interval).
 * 
 * @param x Scalar value
 * @param other Interval
 * @return Resulting interval
 */
IntervalNumber operator*(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) * other;
}

/**
 * Global addition operator (scalar + interval).
 * 
 * @param x Scalar value
 * @param other Interval
 * @return Resulting interval
 */
IntervalNumber operator+(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) + other;
}

/**
 * Global subtraction operator (scalar - interval).
 * 
 * @param x Scalar value
 * @param other Interval
 * @return Resulting interval
 */
IntervalNumber operator-(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) - other;
}

/**
 * Global division operator (scalar / interval).
 * 
 * @param x Scalar value
 * @param other Interval
 * @return Resulting interval
 */
IntervalNumber operator/(double x, const IntervalNumber& other) noexcept
{
    return IntervalNumber(x) / other;
}

/**
 * Global absolute value function.
 * 
 * @param other Interval
 * @return Absolute value as interval
 */
IntervalNumber abs(const IntervalNumber& other) noexcept
{
    return other.abs();
}

/**
 * Global power function (interval ^ scalar).
 * Scalar exponent is converted to interval [exponent, exponent]in.
 * 
 * @param base Base interval
 * @param exponent Scalar exponent
 * @return Resulting interval
 */
IntervalNumber pow(const IntervalNumber& base, double exponent) noexcept
{
    return base.pow(IntervalNumber(exponent));
}

/**
 * Global power function (interval ^ interval).
 * 
 * @param base Base interval
 * @param exponent Exponent interval
 * @return Resulting interval
 */
IntervalNumber pow(const IntervalNumber& base, const IntervalNumber& exponent) noexcept
{
    return base.pow(exponent);
}

#endif /* INTERVALNUMBER_HPP_ */
