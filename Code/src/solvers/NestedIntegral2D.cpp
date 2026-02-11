// NestedIntegral2D.cpp
#include "solvers/NestedIntegral2D.hpp"

#include "core/Function.hpp"
#include "core/Interval.hpp"

namespace integ {

/**
 * @brief Construct a nested 2D integrator
 */
NestedIntegral2D::NestedIntegral2D(
    const Solver& outer_solver,
    const Solver& inner_solver
)
    : outer_(outer_solver), inner_(inner_solver)
{}

/**
 * @brief Compute a 2D integral using nested 1D solvers
 *
 * Performs:
 *   int_{x ∈ domain} [ int_{y_min(x)}^{y_max(x)} f(x, y) dy ] dx
 */
IntegrationResult NestedIntegral2D::integrate(
    const Function2D& f,
    const Domain2D& domain,
    const SolverParams& params
) const
{
    // Inner integral over y for a fixed x
    auto inner_integral = [&](double x) -> double {

        // f(x, y) as a 1D function in y
        class Fy : public Function {
        public:
            Fy(const Function2D& f, double x) : f_(f), x_(x) {}
            double operator()(double y) const override {
                return f_(x_, y);
            }
        private:
            const Function2D& f_;
            double x_;
        };

        Fy fy(f, x);
        Interval Iy(domain.y_min(x), domain.y_max(x));

        return inner_.integrate(fy, Iy, params).value;
    };

    // Outer integrand: result of the inner integral
    class Fx : public Function {
    public:
        Fx(const decltype(inner_integral)& g) : g_(g) {}
        double operator()(double x) const override {
            return g_(x);
        }
    private:
        const decltype(inner_integral)& g_;
    };

    Fx fx(inner_integral);
    return outer_.integrate(fx, domain.x_interval(), params);
}

} // namespace integ