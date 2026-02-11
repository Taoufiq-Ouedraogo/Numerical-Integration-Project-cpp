// CompositeTrapezoid.hpp
#pragma once
#include "core/Solver.hpp"
#include <string>

namespace integ {

/**
 * @brief Composite Trapezoid method for 1D numerical integration.
 * 
 * Approximates the integral of a function over a given interval using
 * equally spaced subintervals and the trapezoid rule.
 */
class CompositeTrapezoidSolver : public Solver {
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
    std::string name() const override { return "CompositeTrapezoid"; }
};

} // namespace integ