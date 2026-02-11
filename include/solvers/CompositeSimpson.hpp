// CompositeSimpson.hpp
#pragma once
#include "core/Solver.hpp"
#include <string>

namespace integ {

/**
 * @brief Composite Simpson's method for 1D numerical integration.
 * 
 * Approximates the integral of a function over an interval using
 * Simpson's rule on equally spaced subintervals.
 */
class CompositeSimpsonSolver : public Solver {
public:
    /**
     * @brief Integrate a function f over interval I
     * @param f Function to integrate
     * @param I Interval of integration
     * @param p Solver parameters (number of subintervals, error estimate, etc.)
     * @return IntegrationResult containing integral value, error, and metadata
     */
    IntegrationResult integrate(
        const Function& f,
        const Interval& I,
        const SolverParams& p
    ) const override;

    /** @brief Return the solver name */
    std::string name() const override { return "CompositeSimpson"; }
};

} // namespace integ