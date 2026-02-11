// T2Transform.hpp
#pragma once
#include <cmath>
#include <memory>
#include <string>
#include "core/Function.hpp"

namespace integ {

/**
 * @brief Transform a 1D integral using x = t^2 substitution.
 * 
 * This changes int_{0}^{1} f(x) dx into int_{0}^{1} f(t^{2}) * 2t dt.
 * Useful for functions not defined at x=0 (e.g., log(x), 1/sqrt(x)).
 */
class T2Transform : public Function {
public:
    /**
     * @brief Construct the transform
     * @param base Base function f(x)
     * @param value_at_t0 Value to use at t=0 (limit)
     * @param custom_name Optional name for logging/printing
     */
    T2Transform(std::shared_ptr<Function> base,
                double value_at_t0,
                std::string custom_name = "")
        : base_(std::move(base)),
          value_at_t0_(value_at_t0),
          custom_name_(std::move(custom_name))
    {}

    /**
     * @brief Evaluate the transformed function at t
     * @param t Input variable
     * @return f(t^2) * 2t (or value_at_t0 if t=0)
     */
    double operator()(double t) const override {
        if (t == 0.0) {
            return value_at_t0_; // limit at t=0
        }
        const double x = t * t;
        return (*base_)(x) * 2.0 * t;
    }

    /**
     * @brief Return the function name
     */
    std::string name() const override {
        if (!custom_name_.empty()) return custom_name_;
        return "T2Transform(" + base_->name() + ")";
    }

private:
    std::shared_ptr<Function> base_;
    double value_at_t0_;
    std::string custom_name_;
};

} // namespace integ