// Function.hpp
#pragma once
#include <string>

namespace integ {

/**
 * @brief Abstract base class for 1D functions.
 * 
 * Defines the interface for evaluating a function and optionally
 * providing a name.
 */
class Function {
public:
    virtual ~Function() = default;

    /**
     * @brief Evaluate the function at a given x.
     * @param x Input value.
     * @return Function value f(x).
     */
    virtual double operator()(double x) const = 0;

    /**
     * @brief Optional function name (for logging or display).
     * @return Name of the function.
     */
    virtual std::string name() const { return "Function"; }
};

} // namespace integ