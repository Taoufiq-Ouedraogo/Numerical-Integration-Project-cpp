// NestedIntegral2D.hpp
#pragma once
#include "core/Function2D.hpp"
#include "core/Domain2D.hpp"
#include "core/Solver.hpp"
#include "core/IntegrationResult.hpp"

namespace integ {

/**
 * @brief Computes a 2D integral using nested 1D solvers.
 * 
 * The outer integral is performed over x, and for each x, 
 * the inner integral is performed over y.
 */
class NestedIntegral2D {
public:
    /**
     * @brief Construct the nested integral
     * @param outer_solver Solver to integrate over x
     * @param inner_solver Solver to integrate over y
     */
    NestedIntegral2D(
        const Solver& outer_solver,
        const Solver& inner_solver
    );

    /**
     * @brief Compute the nested integral
     * @param f 2D function f(x, y)
     * @param domain Domain in x and y
     * @param params Solver parameters
     * @return IntegrationResult with value, error estimate, etc.
     */
    IntegrationResult integrate(
        const Function2D& f,
        const Domain2D& domain,
        const SolverParams& params
    ) const;

private:
    const Solver& outer_; ///< Solver for x-direction
    const Solver& inner_; ///< Solver for y-direction
};

} // namespace integ