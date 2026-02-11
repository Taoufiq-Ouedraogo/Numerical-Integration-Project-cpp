// LogX.hpp
#pragma once
#include "core/Function.hpp"
#include <cmath>

namespace integ {

/**
 * @brief Represents the function f(x) = log(x)
 */
class LogX : public Function {
public:
    /**
     * @brief Evaluate the function at x
     * @param x Input value
     * @return log(x)
     */
    double operator()(double x) const override {
        return std::log(x);
    }
};

} // namespace integ