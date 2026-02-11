// ExpXY2D.hpp
#pragma once
#include "../core/Function2D.hpp"
#include <cmath>

/**
 * @brief Represents the 2D function f(x,y) = exp(-x + y)
 */
class ExpXY2D : public integ::Function2D {
public:
    /**
     * @brief Evaluate the function at (x, y)
     * @param x First coordinate
     * @param y Second coordinate
     * @return Value of exp(-x + y)
     */
    double operator()(double x, double y) const override {
        return std::exp(-x + y);
    }
};
