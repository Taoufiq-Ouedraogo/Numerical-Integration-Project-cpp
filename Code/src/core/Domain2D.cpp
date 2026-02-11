// Domain2D.cpp
#include "core/Domain2D.hpp"

namespace integ {

/**
 * @brief Construct a 2D domain
 */
Domain2D::Domain2D(
    Interval x_interval,
    std::function<double(double)> y_min,
    std::function<double(double)> y_max
)
    : x_(x_interval), y_min_(y_min), y_max_(y_max)
{}

/**
 * @brief Return the x-interval
 */
const Interval& Domain2D::x_interval() const {
    return x_;
}

/**
 * @brief Lower bound in y for a given x
 */
double Domain2D::y_min(double x) const {
    return y_min_(x);
}

/**
 * @brief Upper bound in y for a given x
 */
double Domain2D::y_max(double x) const {
    return y_max_(x);
}

} // namespace integ