// MonteCarloUniform.hpp
#pragma once
#include "core/Solver.hpp"
#include <string>

namespace integ {

/**
 * @brief Monte Carlo integration using uniform sampling.
 * 
 * Generates random points uniformly in the interval and estimates
 * the integral using the average value of the function.
 */
class MonteCarloUniformSolver : public Solver {
public:
    /**
     * @brief Compute the integral of f over the interval I
     * @param f Function to integrate
     * @param I Interval of integration
     * @param p Solver parameters (number of samples, seed, etc.)
     * @return IntegrationResult with value, error estimate, etc.
     */
    IntegrationResult integrate(
        const Function& f,
        const Interval& I,
        const SolverParams& p
    ) const override;

    /**
     * @brief Return the solver name
     */
    std::string name() const override { return "MonteCarloUniform"; }
};

} // namespace integ