#include <cstdio>
#include <limits>

#include "IntervalArithmetic.hpp"

int main(int argc, const char* argv[])
{
    // Using infinty as a constant
    constexpr auto inf = std::numeric_limits<double>::infinity();

    // Checking the lower interval bound
    auto a = 0.0 * 0.0;
    printf("0.0 * 0.0 = %lf\n", a);

    // Checking the upper interval bound
    auto b = 1.0 * inf;
    printf("1.0 * inf = %lf\n", b);

    // Creating the [0, ∞] interval
    auto c = IntervalArithmetic(0.0, inf);
    printf("[%lf, %lf]\n", c.lowerBound(), c.upperBound());

    // Checking the multiplication
    auto d = -1.0 * c;
    printf("[%lf, %lf]\n", d.lowerBound(), d.upperBound());

    // As expected, produces not a number
    auto e = inf - inf;
    printf("inf - inf = %lf\n", e);

    return 0;
}
