// Power.hpp
#pragma once
#include "core/Function.hpp"
#include <cmath>

namespace integ {

/**
 * @brief Represents the function f(x) = x^n
 */
class Power : public Function {
public:
    /**
     * @brief Construct a Power function
     * @param n Exponent for the function
     */
    explicit Power(int n) : n_(n) {}

    /**
     * @brief Evaluate the function at x
     * @param x Input value
     * @return x^n
     */
    double operator()(double x) const override {
        return std::pow(x, n_);
    }

private:
    int n_; ///< Exponent
};

} // namespace integ