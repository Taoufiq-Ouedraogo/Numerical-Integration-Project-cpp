// SumSquaresXY2D.hpp
#pragma once
#include "../core/Function2D.hpp"
#include <cmath>

/**
 * @brief 2D function f(x, y) = x^2 + y^2
 */
class SumSquaresXY2D : public integ::Function2D {
public:
    /**
     * @brief Evaluate the function at (x, y)
     * @param x First variable
     * @param y Second variable
     * @return x^2 + y^2
     */
    double operator()(double x, double y) const override {
        return x*x + y*y;
    }
};