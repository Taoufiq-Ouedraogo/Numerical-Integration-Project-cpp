// GSLIntegrator.cpp
#include "solvers/GSLIntegrator.hpp"

namespace integ {

/**
 * @brief Default constructor
 */
GSLIntegrator::GSLIntegrator() = default;

/**
 * @brief Integrate a function using GSL adaptive integration (QAGS)
 *
 * Uses GSL's `gsl_integration_qags`, which applies adaptive
 * Gauss–Kronrod quadrature on the interval.
 *
 * Absolute and relative tolerances are fixed to 1e-8.
 */
IntegrationResult GSLIntegrator::integrate(
    const Function& f,
    const Interval& I,
    const SolverParams& /*p*/
) const
{
    // Allocate GSL workspace
    gsl_integration_workspace* w =
        gsl_integration_workspace_alloc(1000);

    // Wrap integ::Function into gsl_function
    gsl_function F;
    F.function = [](double x, void* params) -> double {
        return (*static_cast<const Function*>(params))(x);
    };
    F.params = const_cast<Function*>(&f);

    double result = 0.0;
    double error  = 0.0;

    // Adaptive integration
    gsl_integration_qags(&F, I.a(), I.b(),
        1e-8,   // absolute tolerance
        1e-8,   // relative tolerance
        1000,   // max subintervals
        w, &result, &error
    );

    gsl_integration_workspace_free(w);

    IntegrationResult r;
    r.value = result;
    r.evaluations = 1000;
    r.has_error_estimate = true;
    r.error_estimate = error;

    return r;
}

} // namespace integ