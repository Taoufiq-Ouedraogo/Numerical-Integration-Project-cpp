// GaussLegendre.cpp
#include "solvers/GaussLegendre.hpp"
#include <stdexcept>

namespace integ {

/**
 * @brief Construct a Gauss–Legendre solver
 *
 * @param order Quadrature order (2, 3, or 5)
 */
GaussLegendreSolver::GaussLegendreSolver(std::size_t order)
    : order_(order)
{
    if (!(order_ == 2 || order_ == 3 || order_ == 5)) {
        throw std::invalid_argument(
            "GaussLegendre: order must be 2, 3, or 5"
        );
    }
}

/**
 * @brief Solver name including quadrature order
 */
std::string GaussLegendreSolver::name() const {
    return "GaussLegendre(order=" + std::to_string(order_) + ")";
}

/**
 * @brief Integrate using Gauss–Legendre quadrature
 *
 * Uses fixed nodes and weights on [-1,1], mapped
 * affinely to the interval [a,b].
 *
 * No error estimate is provided.
 */
IntegrationResult GaussLegendreSolver::integrate(
    const Function& f,
    const Interval& I,
    const SolverParams& /*p*/
) const
{
    // Nodes and weights on [-1,1]
    const double* x = nullptr;
    const double* w = nullptr;
    std::size_t m = 0;

    static const double x2[] = { -0.5773502691896257,  0.5773502691896257 };
    static const double w2[] = {  1.0,                 1.0 };

    static const double x3[] = {
        -0.7745966692414834, 0.0, 0.7745966692414834
    };
    static const double w3[] = {
         0.5555555555555556, 0.8888888888888888, 0.5555555555555556
    };

    static const double x5[] = {
        -0.9061798459386640, -0.5384693101056831, 0.0,
         0.5384693101056831,  0.9061798459386640
    };
    static const double w5[] = {
         0.2369268850561891, 0.4786286704993665, 0.5688888888888889,
         0.4786286704993665, 0.2369268850561891
    };

    // Select rule
    if (order_ == 2)      { x = x2; w = w2; m = 2; }
    else if (order_ == 3) { x = x3; w = w3; m = 3; }
    else                  { x = x5; w = w5; m = 5; }

    const double a = I.a();
    const double b = I.b();

    // Affine transform from [-1,1] to [a,b]
    const double mid  = 0.5 * (a + b);
    const double half = 0.5 * (b - a);

    double sum = 0.0;
    for (std::size_t i = 0; i < m; ++i) {
        const double u = mid + half * x[i];
        sum += w[i] * f(u);
    }

    IntegrationResult res;
    res.value = half * sum;
    res.evaluations = m;
    res.has_error_estimate = false;

    return res;
}

} // namespace integ