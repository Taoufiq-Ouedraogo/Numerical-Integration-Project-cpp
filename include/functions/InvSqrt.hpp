// InvSqrt.hpp
#pragma once
#include "core/Function.hpp"
#include <cmath>

namespace integ {

/**
 * @brief Represents the function f(x) = 1 / sqrt(x)
 */
class InvSqrt : public Function {
public:
    /**
     * @brief Evaluate the function at x
     * @param x Input value
     * @return 1 / sqrt(x)
     */
    double operator()(double x) const override {
        return 1.0 / std::sqrt(x);
    }
};

} // namespace integ