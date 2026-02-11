// Interval.cpp
#include "core/Interval.hpp"

namespace integ {

/**
 * @brief Construct an interval [a, b]
 *
 * @throws std::invalid_argument if b <= a
 */
Interval::Interval(double a, double b)
    : a_(a), b_(b)
{
    if (b <= a) {
        throw std::invalid_argument(
            "Interval error: b must be strictly greater than a"
        );
    }
}

/**
 * @brief Left endpoint of the interval
 */
double Interval::a() const noexcept {
    return a_;
}

/**
 * @brief Right endpoint of the interval
 */
double Interval::b() const noexcept {
    return b_;
}

/**
 * @brief Length of the interval (b - a)
 */
double Interval::length() const noexcept {
    return b_ - a_;
}

} // namespace integ