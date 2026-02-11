// PolyX2Cos.hpp
#pragma once
#include "core/Function.hpp"
#include <cmath>

namespace integ {

/**
 * @brief Represents the function f(x) = x^2 * cos(x)
 */
class PolyX2Cos : public Function {
public:
    /**
     * @brief Evaluate the function at x
     * @param x Input value
     * @return x^2 * cos(x)
     */
    double operator()(double x) const override {
        return x * x * std::cos(x);
    }
};

} // namespace integ