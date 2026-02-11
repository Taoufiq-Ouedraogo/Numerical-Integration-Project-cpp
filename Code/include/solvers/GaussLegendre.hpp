// GaussLegendre.hpp
#pragma once
#include "core/Solver.hpp"
#include <string>
#include <cstddef>

namespace integ {

/**
 * @brief Gauss-Legendre quadrature solver for 1D integration.
 * 
 * Approximates the integral using Gauss-Legendre quadrature of a given order.
 */
class GaussLegendreSolver : public Solver {
public:
    /**
     * @brief Construct a Gauss-Legendre solver
     * @param order Number of points in quadrature (default 5)
     */
    explicit GaussLegendreSolver(std::size_t order = 5);

    /**
     * @brief Integrate a function f over interval I
     * @param f Function to integrate
     * @param I Interval of integration
     * @param p Solver parameters (unused here but included for consistency)
     * @return IntegrationResult containing integral value, error, and metadata
     */
    IntegrationResult integrate(
        const Function& f,
        const Interval& I,
        const SolverParams& p
    ) const override;

    /** @brief Return the solver name */
    std::string name() const override;

private:
    std::size_t order_; ///< Quadrature order (2, 3, or 5)
};

} // namespace integ