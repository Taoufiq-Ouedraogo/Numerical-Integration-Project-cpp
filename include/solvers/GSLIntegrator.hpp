// GSLIntegrator.hpp
#pragma once
#include "../core/Solver.hpp"
#include "../core/Function.hpp"
#include "../core/Interval.hpp"
#include <gsl/gsl_integration.h>
#include <string>

namespace integ {

/**
 * @brief Integration using GSL (GNU Scientific Library) routines.
 * 
 * Uses GSL adaptive integration methods to compute definite integrals
 * of 1D functions over a given interval.
 */
struct GSLIntegrator : public Solver {
    /** @brief Default constructor */
    GSLIntegrator();

    /**
     * @brief Integrate a function f over interval I
     * @param f Function to integrate
     * @param I Interval of integration
     * @param params Solver parameters (subdivisions, samples, etc.)
     * @return IntegrationResult containing integral value, error, and metadata
     */
    IntegrationResult integrate(
        const Function& f,
        const Interval& I,
        const SolverParams& params
    ) const override;

    /** @brief Return the solver name */
    std::string name() const override { return "GSLIntegrator"; }
};

} // namespace integ