// SinXY2D.hpp
#pragma once
#include "../core/Function2D.hpp"
#include <cmath>

/**
 * @brief 2D function f(x, y) = sin(x + y)
 */
class SinXY2D : public integ::Function2D {
public:
    /**
     * @brief Evaluate the function at (x, y)
     * @param x First variable
     * @param y Second variable
     * @return sin(x + y)
     */
    double operator()(double x, double y) const override {
        return std::sin(x + y);
    }
};