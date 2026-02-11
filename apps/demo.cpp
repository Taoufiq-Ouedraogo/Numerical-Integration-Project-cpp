// demo.cpp
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <cmath>
#include <limits>
#include <sstream>
#include <fstream>
#include <filesystem>

#include "core/Interval.hpp"
#include "core/Domain2D.hpp"
#include "core/Function.hpp"
#include "core/Function2D.hpp"
#include "core/Solver.hpp"

#include "functions/Power.hpp"
#include "functions/PolyX2Cos.hpp"
#include "functions/InvSqrt.hpp"
#include "functions/LogX.hpp"
#include "functions/T2Transform.hpp"
#include "functions/ProductXY2D.hpp"
#include "functions/SumSquaresXY2D.hpp"
#include "functions/SinXY2D.hpp"
#include "functions/ExpXY2D.hpp"

#include "solvers/CompositeTrapezoid.hpp"
#include "solvers/CompositeSimpson.hpp"
#include "solvers/MonteCarloUniform.hpp"
#include "solvers/GaussLegendre.hpp"
#include "solvers/GSLIntegrator.hpp"
#include "solvers/NestedIntegral2D.hpp"


struct Problem {
    std::string label;
    std::shared_ptr<integ::Function> f;
    integ::Interval I;
    double exact;
    bool exact_available;
};

struct CsvRow {
    std::string function;
    std::string interval;
    std::string solver;
    double approx{};
    double exact{};
    bool exact_available{};
    double abs_error{};
    std::size_t evals{};
    bool has_err_est{};
    double err_est{};
};

// --- CSV helpers ---
static std::string csv_escape(const std::string& s) {
    const bool need_quotes = (s.find(',') != std::string::npos) || (s.find('"') != std::string::npos);
    if (!need_quotes) return s;
    std::string t;
    t.reserve(s.size() + 2);
    t.push_back('"');
    for (char c : s) t += (c == '"') ? "\"\"" : std::string(1, c);
    t.push_back('"');
    return t;
}

static void write_csv(const std::string& path, const std::vector<CsvRow>& rows) {
    namespace fs = std::filesystem;
    fs::path p(path);
    if (p.has_parent_path()) fs::create_directories(p.parent_path());

    std::ofstream out(path);
    if (!out) throw std::runtime_error("Impossible d'ouvrir le CSV: " + path);

    out << "Function,Interval,Solver,Approx,Exact,AbsError,Evals,ErrEst\n";
    out << std::setprecision(17);

    for (const auto& r : rows) {
        out << csv_escape(r.function) << ","
            << csv_escape(r.interval) << ","
            << csv_escape(r.solver) << ","
            << r.approx << ",";

        if (r.exact_available) out << r.exact << "," << r.abs_error << ",";
        else out << "N/A,N/A,";

        out << r.evals << ",";
        if (r.has_err_est) out << r.err_est;
        else out << "-";
        out << "\n";
    }
}

static std::string get_output_path(int argc, char** argv) {
    std::string out = "outputs/results.csv";
    for (int i = 1; i + 1 < argc; ++i) {
        if (std::string(argv[i]) == "--output") out = argv[i + 1];
    }
    return out;
}

static void print_header() {
    std::cout
        << std::left
        << std::setw(20) << "Function"
        << std::setw(28) << "Interval / Domain (x,y)"
        << std::setw(24) << "Solver"
        << std::right
        << std::setw(22) << "Approx"
        << std::setw(22) << "Exact"
        << std::setw(22) << "AbsError"
        << std::setw(14) << "Evals"
        << std::setw(22) << "ErrEst"
        << "\n";

    std::cout << std::string(20 + 28 + 24 + 22 + 22 + 22 + 14 + 22, '-') << "\n";
}

static std::string interval_str(const integ::Interval& I) {
    std::ostringstream oss;
    oss << "[" << I.a() << ", " << I.b() << "]";
    return oss.str();
}

static std::string domain_str(const integ::Domain2D& D, int n_samples=5) {
    double xmin = D.x_interval().a();
    double xmax = D.x_interval().b();

    double ymin = std::numeric_limits<double>::max();
    double ymax = std::numeric_limits<double>::lowest();
    for (int i=0; i<=n_samples; ++i) {
        double x = xmin + i*(xmax-xmin)/n_samples;
        ymin = std::min(ymin, D.y_min(x));
        ymax = std::max(ymax, D.y_max(x));
    }
    std::ostringstream oss;
    oss << "[" << xmin << ", " << xmax << "] × [" << ymin << ", " << ymax << "]";
    return oss.str();
}

static void print_row_safe(const std::string& func_label,
                           const std::string& interval_str,
                           const integ::Solver& solver,
                           const integ::IntegrationResult& r,
                           double exact,
                           bool exact_available)
{
    std::cout << std::left
              << std::setw(20) << func_label
              << std::setw(28) << interval_str
              << std::setw(24) << solver.name()
              << std::right;

    if (r.success) {
        double abs_err = exact_available ? std::abs(r.value - exact) : std::numeric_limits<double>::quiet_NaN();
        std::cout << std::setw(22) << r.value;
        if (exact_available) std::cout << std::setw(22) << exact << std::setw(22) << abs_err;
        else std::cout << std::setw(22) << "N/A" << std::setw(22) << "N/A";
        std::cout << std::setw(14) << r.evaluations;
        if (r.has_error_estimate) std::cout << std::setw(22) << r.error_estimate;
        else std::cout << std::setw(22) << "-";
    } else {
        std::cout << std::setw(22) << "FAILED"
                  << std::setw(22) << "N/A"
                  << std::setw(22) << "N/A"
                  << std::setw(14) << "-"
                  << std::setw(22) << "-";
    }

    std::cout << "\n";
}

int main(int argc, char** argv) {
    using namespace integ;

    std::cout << std::setprecision(15);

    std::vector<Problem> problems;

    // --- 1D problems ---
    problems.push_back({"x^10", std::make_shared<Power>(10), Interval(0.0,1.0), 1.0/11.0, true});
    problems.push_back({"x^2 cos(x)", std::make_shared<PolyX2Cos>(), Interval(0.0,1.0), 2.0*std::cos(1.0)-std::sin(1.0), true});
    {
        auto f_base = std::make_shared<InvSqrt>();
        auto f_t2 = std::make_shared<T2Transform>(f_base, 2.0, "x^(-1/2) (x=t^2)");
        problems.push_back({"x^(-1/2)", f_t2, Interval(0.0,1.0), 2.0, true});
    }
    {
        auto f_base = std::make_shared<LogX>();
        auto f_t2 = std::make_shared<T2Transform>(f_base, 0.0, "log(x) (x=t^2)");
        problems.push_back({"log(x)", f_t2, Interval(0.0,1.0), -1.0, true});
    }

    // --- 1D Solvers ---
    CompositeTrapezoidSolver trap;
    CompositeSimpsonSolver simp;
    MonteCarloUniformSolver mc;
    GaussLegendreSolver gl5(5);
    GSLIntegrator gsl_solver;

    // --- 1D Integration Demo ---
    std::cout << "\n\n##### 1D Integration Demo #####\n\n";
    print_header();
    std::vector<CsvRow> rows;

    for (const auto& pb : problems) {
        SolverParams p;
        p.n = 2000;

        auto run_solver_safe = [&](integ::Solver& solver, SolverParams params) {
            integ::IntegrationResult r;
            try {
                r = solver.integrate(*pb.f, pb.I, params);
                r.success = true;
            } catch (...) {
                r = integ::IntegrationResult{};
                r.success = false;
            }
            print_row_safe(pb.label, interval_str(pb.I), solver, r, pb.exact, pb.exact_available);

            rows.push_back({pb.label, interval_str(pb.I), solver.name(), r.value, pb.exact,
                            pb.exact_available, r.success ? std::abs(r.value - pb.exact) : std::numeric_limits<double>::quiet_NaN(),
                            r.evaluations, r.has_error_estimate, r.error_estimate});
        };

        run_solver_safe(trap, p);
        run_solver_safe(simp, p);
        run_solver_safe(gl5, p);

        p.n_samples = 200000; p.seed = 42; p.compute_error_estimate = true;
        run_solver_safe(mc, p);
        run_solver_safe(gsl_solver, p);

        std::cout << "\n";
    }

    // --- 2D Integration Demo ---
    std::cout << "\n\n##### 2D Integration Demo #####\n\n";
    print_header();
    std::vector<CsvRow> rows2D;

    std::vector<std::tuple<std::string, std::shared_ptr<integ::Function2D>, double>> f2d_list = {
        {"x*y", std::make_shared<ProductXY2D>(), 1.25},
        {"x^2+y^2", std::make_shared<SumSquaresXY2D>(), 19.0/9.0},
        {"sin(x+y)", std::make_shared<SinXY2D>(), -std::sin(4.0) + 2.0*std::sin(3.0) - std::sin(2.0)},
        {"exp(-x+y)", std::make_shared<ExpXY2D>(), std::exp(3.0) - 2.0*std::exp(2.0) + std::exp(1.0)}
    };

    Domain2D domain2d(
        Interval(0,1),
        [](double){ return 2.0; },
        [](double){ return 3.0; }
    );

    std::vector<std::pair<std::shared_ptr<Solver>, std::shared_ptr<Solver>>> solver_pairs = {
        {std::make_shared<CompositeTrapezoidSolver>(), std::make_shared<CompositeTrapezoidSolver>()},
        {std::make_shared<CompositeSimpsonSolver>(),     std::make_shared<CompositeSimpsonSolver>()},
        {std::make_shared<GaussLegendreSolver>(5),      std::make_shared<GaussLegendreSolver>(5)}
        //{std::make_shared<MonteCarloUniformSolver>(),     std::make_shared<MonteCarloUniformSolver>()},
        //{std::make_shared<GSLIntegrator>(),     std::make_shared<GSLIntegrator>()},
    };

    for (auto& [label, f2d, exact] : f2d_list) {
        for (auto& [outer, inner] : solver_pairs) {
            NestedIntegral2D nested(*outer, *inner);
            SolverParams p2d;
            p2d.n = 2000; p2d.n_samples = 200000; p2d.compute_error_estimate = true;

            integ::IntegrationResult r2d;
            try {
                r2d = nested.integrate(*f2d, domain2d, p2d);
                r2d.success = true;
            } catch (...) {
                r2d = integ::IntegrationResult{};
                r2d.success = false;
            }

            print_row_safe(label, domain_str(domain2d), *outer, r2d, exact, true);  
            rows2D.push_back({label, domain_str(domain2d), outer->name(), r2d.value, exact, true,
                              r2d.success ? std::abs(r2d.value - exact) : std::numeric_limits<double>::quiet_NaN(),
                              r2d.evaluations, r2d.has_error_estimate, r2d.error_estimate});
        }
        std::cout << "\n";
    }

    // --- Write CSV for both 1D and 2D ---
    const std::string out_path = get_output_path(argc, argv);
    std::vector<CsvRow> all_rows = rows;
    all_rows.insert(all_rows.end(), rows2D.begin(), rows2D.end());
    write_csv(out_path, all_rows);

    std::cout << "\nCSV écrit dans: " << out_path << "\n\n";

    return 0;
}