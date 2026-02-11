// Function2D.hpp
#pragma once

namespace integ {

/**
 * @brief Abstract base class for 2D functions.
 * 
 * Defines the interface for evaluating a function of two variables.
 */
class Function2D {
public:
    virtual ~Function2D() = default;

    /**
     * @brief Evaluate the function at given (x, y) coordinates.
     * @param x First input variable.
     * @param y Second input variable.
     * @return Function value f(x, y).
     */
    virtual double operator()(double x, double y) const = 0;
};

} // namespace integ