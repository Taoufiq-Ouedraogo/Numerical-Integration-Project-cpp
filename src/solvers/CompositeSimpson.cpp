// CompositeSimpson.cpp
#include "solvers/CompositeSimpson.hpp"
#include <stdexcept>

namespace integ {

/**
 * @brief Integrate using the composite Simpson's rule
 *
 * Approximates
 * \f[
 * \int_a^b f(x)\,dx
 * \approx \frac{h}{3}
 * \left[
 * f(a) + f(b)
 * + 4 \sum_{\text{odd } i} f(x_i)
 * + 2 \sum_{\text{even } i} f(x_i)
 * \right]
 * \f]
 *
 * where:
 * - n is even
 * - h = (b - a) / n
 * - x_i = a + i h
 *
 * No error estimate is provided.
 */
IntegrationResult CompositeSimpsonSolver::integrate(
    const Function& f,
    const Interval& I,
    const SolverParams& p
) const
{
    // Simpson requires at least two subintervals
    if (p.n < 2) {
        throw std::invalid_argument(
            "CompositeSimpson: n must be >= 2"
        );
    }

    // n must be even
    if (p.n % 2 != 0) {
        throw std::invalid_argument(
            "CompositeSimpson: n must be even"
        );
    }

    const double a = I.a();
    const double b = I.b();
    const std::size_t n = p.n;
    const double h = (b - a) / static_cast<double>(n);

    // Endpoints contribution
    double sum = f(a) + f(b);

    // Odd indices (weight 4)
    for (std::size_t i = 1; i < n; i += 2) {
        const double x = a + h * static_cast<double>(i);
        sum += 4.0 * f(x);
    }

    // Even indices (weight 2)
    for (std::size_t i = 2; i < n; i += 2) {
        const double x = a + h * static_cast<double>(i);
        sum += 2.0 * f(x);
    }

    IntegrationResult res;
    res.value = (h / 3.0) * sum;
    res.evaluations = n + 1;   // a, b, and (n-1) interior points
    res.has_error_estimate = false;

    return res;
}

} // namespace integ