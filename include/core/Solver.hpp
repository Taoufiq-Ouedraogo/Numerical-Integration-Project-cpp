// Solver.hpp
#pragma once
#include <cstddef>
#include <optional>
#include <random>
#include <string>
#include <iostream>
#include <limits>

#include "core/Interval.hpp"
#include "core/IntegrationResult.hpp"
#include "core/Function.hpp"

namespace integ {

/**
 * @brief Parameters for solvers.
 */
struct SolverParams {
    // Grid-based methods
    std::size_t n = 1000;                 ///< Number of subintervals

    // Monte Carlo
    std::size_t n_samples = 100000;       ///< Number of samples
    std::optional<std::uint32_t> seed;    ///< Optional RNG seed

    // Misc
    bool compute_error_estimate = true;   ///< Whether to compute error estimate
};

/**
 * @brief Base class for 1D integration solvers.
 */
class Solver {
public:
    virtual ~Solver() = default;

    /**
     * @brief Integrates safely, catching exceptions.
     * 
     * If the integration fails, sets success=false and fills default values.
     * 
     * @param f Function to integrate
     * @param I Interval
     * @param p Solver parameters
     * @return IntegrationResult with success flag
     */
    IntegrationResult integrate_safe(
        const Function& f,
        const Interval& I,
        const SolverParams& p
    ) const {
        IntegrationResult result;
        try {
            result = integrate(f, I, p);  // call derived solver
            result.success = true;
        } catch (const std::exception& /*e*/) {
            result.success = false;
            result.value = std::numeric_limits<double>::quiet_NaN();
            result.evaluations = 0;
            result.error_estimate = 0.0;
            result.has_error_estimate = false;
        } 
        return result;
    }

    /**
     * @brief Actual integration method implemented by derived solvers.
     * @param f Function to integrate
     * @param I Interval
     * @param p Solver parameters
     * @return IntegrationResult
     */
    virtual IntegrationResult integrate(
        const Function& f,
        const Interval& I,
        const SolverParams& p
    ) const = 0;

    /** @brief Name of the solver */
    virtual std::string name() const { return "Solver"; }
};

} // namespace integ