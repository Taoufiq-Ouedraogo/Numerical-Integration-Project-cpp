// Domain2D.hpp
#pragma once
#include <functional>
#include "Interval.hpp"

namespace integ {

/**
 * @brief Represents a 2D domain for integration.
 * 
 * The domain is defined by an interval in x and functions
 * that give the minimum and maximum y-values for each x.
 */
class Domain2D {
public:
    /**
     * @brief Construct a 2D domain.
     * @param x_interval Interval for the x-axis.
     * @param y_min Function returning minimum y for a given x.
     * @param y_max Function returning maximum y for a given x.
     */
    Domain2D(
        Interval x_interval,
        std::function<double(double)> y_min,
        std::function<double(double)> y_max
    );

    /// @brief Get the x-interval.
    const Interval& x_interval() const;

    /// @brief Get the minimum y for a given x.
    double y_min(double x) const;

    /// @brief Get the maximum y for a given x.
    double y_max(double x) const;

private:
    Interval x_;
    std::function<double(double)> y_min_;
    std::function<double(double)> y_max_;
};

} // namespace integ