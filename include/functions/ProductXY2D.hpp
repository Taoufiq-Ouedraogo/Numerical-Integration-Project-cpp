// ProductXY2D.hpp
#pragma once
#include "../core/Function2D.hpp"

/**
 * @brief 2D function f(x, y) = x * y
 */
class ProductXY2D : public integ::Function2D {
public:
    /**
     * @brief Evaluate the function at (x, y)
     * @param x First variable
     * @param y Second variable
     * @return x * y
     */
    double operator()(double x, double y) const override {
        return x * y;
    }
};