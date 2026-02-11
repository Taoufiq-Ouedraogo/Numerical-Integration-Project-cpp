// MonteCarloUniform.cpp
#include "solvers/MonteCarloUniform.hpp"
#include <random>
#include <stdexcept>
#include <cmath>

namespace integ {

/**
 * @brief Monte Carlo integration with uniform sampling
 *
 * Approximates:
 * \[
 * \int_a^b f(x)\,dx \approx (b-a)\,\frac{1}{n}\sum_{i=1}^n f(X_i),
 * \quad X_i \sim \mathcal{U}(a,b)
 * \]
 *
 * Uses Welford's algorithm for numerically stable
 * mean and variance estimation.
 */
IntegrationResult MonteCarloUniformSolver::integrate(
    const Function& f,
    const Interval& I,
    const SolverParams& p
) const
{
    if (p.n_samples == 0) {
        throw std::invalid_argument(
            "MonteCarloUniform: n_samples must be >= 1"
        );
    }

    const double a = I.a();
    const double b = I.b();
    const double L = I.length();
    const std::size_t n = p.n_samples;

    // Random number generator
    std::mt19937 rng;
    if (p.seed.has_value()) {
        rng.seed(*p.seed);
    } else {
        rng.seed(std::random_device{}());
    }

    std::uniform_real_distribution<double> unif(a, b);

    // Welford's algorithm for mean and variance
    double mean = 0.0;
    double m2 = 0.0;

    for (std::size_t i = 1; i <= n; ++i) {
        const double x = unif(rng);
        const double y = f(x);

        const double delta = y - mean;
        mean += delta / static_cast<double>(i);
        const double delta2 = y - mean;
        m2 += delta * delta2;
    }

    const double var_f =
        (n > 1) ? (m2 / static_cast<double>(n - 1)) : 0.0;

    const double estimate = L * mean;

    IntegrationResult res;
    res.value = estimate;
    res.evaluations = n;

    /**
     * Standard error:
     * \[
     * \sigma_{\hat I} = (b-a)\sqrt{\frac{\mathrm{Var}(f)}{n}}
     * \]
     */
    if (p.compute_error_estimate && n > 1) {
        res.has_error_estimate = true;
        res.error_estimate =
            L * std::sqrt(var_f / static_cast<double>(n));
        res.meta["var_f"] = var_f;
    }

    // Store seed if explicitly provided (for reproducibility)
    if (p.seed.has_value()) {
        res.meta["seed"] = static_cast<double>(*p.seed);
    }

    return res;
}

} // namespace integ