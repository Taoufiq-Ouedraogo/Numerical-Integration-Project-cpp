// CompositeTrapezoid.cpp
#include "solvers/CompositeTrapezoid.hpp"
#include <stdexcept>

namespace integ {

/**
 * @brief Integrate using the composite trapezoidal rule
 *
 * Approximates
 * \f[
 * \int_a^b f(x)\,dx
 * \approx h \left[
 * \tfrac12 f(a) + \sum_{i=1}^{n-1} f(a + ih) + \tfrac12 f(b)
 * \right]
 * \f]
 *
 * where h = (b - a) / n.
 *
 * No error estimate is provided.
 */
IntegrationResult CompositeTrapezoidSolver::integrate(
    const Function& f,
    const Interval& I,
    const SolverParams& p
) const
{
    // Number of subintervals must be positive
    if (p.n == 0) {
        throw std::invalid_argument(
            "CompositeTrapezoid: n must be >= 1"
        );
    }

    const double a = I.a();
    const double b = I.b();
    const std::size_t n = p.n;
    const double h = (b - a) / static_cast<double>(n);

    double sum = 0.0;

    // Endpoints
    sum += 0.5 * f(a);
    sum += 0.5 * f(b);

    // Interior points
    for (std::size_t i = 1; i < n; ++i) {
        const double x = a + h * static_cast<double>(i);
        sum += f(x);
    }

    IntegrationResult res;
    res.value = h * sum;
    res.evaluations = n + 1;   // a, b, and (n-1) interior points
    res.has_error_estimate = false;

    return res;
}

} // namespace integ