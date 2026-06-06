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
     * Interval division: [x0,x1]in / [y0,y1]in := [x0,x1]in * (1/[y0,y1]in)
     *
     * Reciprocal of [y0, y1] is computed by case analysis (see paper §4.4):
     *   - [0, 0]                   -> [-∞, ∞]   (paper convention; division total)
     *   - y0 > 0, y1 > 0           -> [1/y1, 1/y0]
     *   - y1 < 0, y0 < 0           -> [1/y1, 1/y0]
     *   - y0 == 0, y1 > 0          -> [1/y1, +∞]   (1/0+ = +∞)
     *   - y0 < 0, y1 == 0          -> [-∞, 1/y0]   (1/0- = -∞)
     *   - y0 < 0 < y1 (zero-spanning) -> [-∞, +∞] (loss of tightness; hull of two unbounded branches)
     *
     * Indeterminate forms emerging from this scheme:
     *   - 0/0 = [0,0] * [-∞, ∞] = [-∞, ∞]
     *   - ∞/∞ = [∞,∞] * [0,0] = [0, ∞]   (via 0·∞ rule in operator*)
     *
     * @param other The interval to divide by
     * @return Resulting interval
     */
    IntervalNumber operator/(const IntervalNumber& other) const noexcept
    {
        // NaN propagation
        if (std::isnan(m_interval[0u]) || std::isnan(other.m_interval[0u]))
        {
            return IntervalNumber(QUIET_NAN);
        }

        const double y0 = other.m_interval[0u];
        const double y1 = other.m_interval[1u];

        // Divisor is the point [0, 0]: by convention, division returns the full hull.
        if (y0 == 0.0 && y1 == 0.0)
        {
            return IntervalNumber(-INF, INF);
        }

        double r_lo;
        double r_hi;

        if (y0 > 0.0)
        {
            // Strictly positive divisor.
            r_lo = 1.0 / y1;
            r_hi = 1.0 / y0;
        }
        else if (y1 < 0.0)
        {
            // Strictly negative divisor.
            r_lo = 1.0 / y1;
            r_hi = 1.0 / y0;
        }
        else if (y0 == 0.0)
        {
            // [0, y1] with y1 > 0; lower bound of reciprocal is 1/y1, upper is +∞.
            r_lo = 1.0 / y1;
            r_hi = INF;
        }
        else if (y1 == 0.0)
        {
            // [y0, 0] with y0 < 0; lower bound is -∞, upper is 1/y0 (negative).
            r_lo = -INF;
            r_hi = 1.0 / y0;
        }
        else
        {
            // y0 < 0 < y1: divisor strictly contains zero. The exact reciprocal
            // is (-∞, 1/y0] ∪ [1/y1, +∞); to preserve closure within \mathcal{I}
            // we take the convex hull, which is [-∞, +∞]. This is sound but
            // not tight (paper §4.4, Limitation 2).
            r_lo = -INF;
            r_hi = INF;
        }

        return *this * IntervalNumber(r_lo, r_hi);
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
     * Absolute value of interval (defined by order, not by endpoint product):
     *   |[x0, x1]|in = [x0, x1]                       if 0 <= x0
     *   |[x0, x1]|in = [-x1, -x0]                     if x1 <= 0
     *   |[x0, x1]|in = [0, max(-x0, x1)]              if x0 < 0 < x1
     *
     * Using order rather than the product x0·x1 avoids the indeterminate form
     * 0·∞ that would arise for intervals such as [0, ∞] or [-∞, 0]
     * (paper §4.6).
     *
     * @return Absolute value as interval
     */
    IntervalNumber abs() const noexcept
    {
        const double a0 = m_interval[0u];
        const double a1 = m_interval[1u];

        if (std::isnan(a0) || std::isnan(a1))
        {
            return IntervalNumber(QUIET_NAN);
        }

        if (a0 >= 0.0)
        {
            return IntervalNumber(a0, a1);
        }
        if (a1 <= 0.0)
        {
            return IntervalNumber(-a1, -a0);
        }
        return IntervalNumber(0.0, std::max(-a0, a1));
    }

    /**
     * Power operation: [x0,x1]in ^ [y0,y1]in
     * 
     * Computes interval raised to an interval power.
     * The result is the union of all possible powers: base^exp for all base in [x0,x1], exp in [y0,y1]
     * 
     * Handles indeterminate forms via the value map V^ at every reachable
     * indeterminate-form corner (0,0), (1, +/- inf), (+/- inf, 0): whenever
     * such a corner lies in [x0,x1] x [y0,y1] the hull contains 0 and +inf.
     * 
     * General approach: compute base^exp for all combinations of interval endpoints.
     * Scalar exponents are automatically converted to single-point intervals.
     */
    IntervalNumber pow(const IntervalNumber& exponent) const noexcept
    {
        const double bLo = m_interval[0u];
        const double bHi = m_interval[1u];
        const double eLo = exponent.m_interval[0u];
        const double eHi = exponent.m_interval[1u];

        // NaN propagation.
        if (std::isnan(bLo) || std::isnan(bHi) || std::isnan(eLo) || std::isnan(eHi))
        {
            return IntervalNumber(QUIET_NAN);
        }

        // Admissible domain (paper Def. 4.7). Exponentiation is partial; for
        // any pair (I, E) outside the admissible domain the operation is
        // mathematically undefined and is reported as NaN. The admissible
        // cases are:
        //   (i)   base strictly positive            (bLo > 0)
        //   (ii)  base and exponent non-negative     (bLo >= 0 and eLo >= 0)
        //   (iii) exponent a single non-neg integer  (E = {n}, n >= 0)
        //   (iv)  exponent a single neg integer and  (E = {n}, n < 0, 0 not in I)
        const bool baseContainsZero = (bLo <= 0.0 && bHi >= 0.0);
        const bool exponentIsPointInteger =
            (eLo == eHi) && std::isfinite(eLo) && (std::floor(eLo) == eLo);

        bool admissible = false;
        if (bLo > 0.0)
        {
            admissible = true;                                          // (i)
        }
        else if (bLo >= 0.0 && eLo >= 0.0)
        {
            admissible = true;                                          // (ii)
        }
        else if (exponentIsPointInteger && eLo >= 0.0)
        {
            admissible = true;                                          // (iii)
        }
        else if (exponentIsPointInteger && eLo < 0.0 && !baseContainsZero)
        {
            admissible = true;                                          // (iv)
        }

        if (!admissible)
        {
            return IntervalNumber(QUIET_NAN);
        }

        std::set<double> results{};

        // Value map V^ at the indeterminate-form corners reachable within
        // I x E: (0,0), (1, +/-inf) and (+/-inf, 0). Whenever such a corner
        // lies in I x E the hull contains both 0 and +inf.
        const bool baseContainsOne = (bLo <= 1.0 && bHi >= 1.0);
        const bool baseContainsInf = (bHi == INF) || (bLo == -INF);
        const bool expContainsZero = (eLo <= 0.0 && eHi >= 0.0);
        const bool expContainsInf  = (eHi == INF) || (eLo == -INF);

        if ((baseContainsZero && expContainsZero) ||   // (0, 0)
            (baseContainsOne  && expContainsInf)  ||   // (1, +/-inf)
            (baseContainsInf  && expContainsZero))     // (+/-inf, 0)
        {
            results.insert(0.0);
            results.insert(INF);
        }

        // Endpoint (corner) values. On the admissible domain (x, y) -> x^y is
        // monotone on each sign-constant subrectangle, so its extrema are
        // attained at corners -- with the sole exception of the interior
        // minimum of an even positive-integer power over a zero-spanning base,
        // handled separately below. No corner can be NaN on the admissible
        // domain (negative bases occur only with integer exponents).
        for (std::size_t i = 0u; i < 2u; i++)
        {
            for (std::size_t j = 0u; j < 2u; j++)
            {
                const double r = std::pow(m_interval[i], exponent.m_interval[j]);
                if (!std::isnan(r))
                {
                    results.insert(r);
                }
            }
        }

        // Interior minimum: x^n for an even integer n > 0 attains 0 inside a
        // base interval that strictly spans zero (paper Def. 4.7, reduction
        // to corner formulas, even-exponent case).
        if (exponentIsPointInteger && eLo > 0.0 && bLo < 0.0 && bHi > 0.0 &&
            std::fmod(eLo, 2.0) == 0.0)
        {
            results.insert(0.0);
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
