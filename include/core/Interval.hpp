// Interval.hpp 
#pragma once
#include <stdexcept>
#include <string>

namespace integ {

/**
 * @brief Represents a 1D interval [a, b].
 */
class Interval {
public:
    /**
     * @brief Construct an interval [a, b]
     * @param a Lower bound
     * @param b Upper bound (must be >= a)
     * @throws std::invalid_argument if b < a
     */
    Interval(double a, double b);

    /** @brief Get lower bound */
    double a() const noexcept;

    /** @brief Get upper bound */
    double b() const noexcept;

    /** @brief Get interval length (b - a) */
    double length() const noexcept;

private:
    double a_; ///< Lower bound
    double b_; ///< Upper bound
};

} // namespace integ