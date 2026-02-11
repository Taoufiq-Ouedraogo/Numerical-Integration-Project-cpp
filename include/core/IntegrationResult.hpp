// IntegrationResult.hpp
#pragma once
#include <cstddef>
#include <map>
#include <string>

namespace integ {

/**
 * @brief Stores the result of an integration.
 * 
 * Contains the approximate value, number of evaluations, optional error estimate,
 * metadata, and a success flag indicating whether the integration succeeded.
 */
struct IntegrationResult {
    double value = 0.0;                 ///< Approximate integral value
    std::size_t evaluations = 0;        ///< Number of function evaluations
    bool has_error_estimate = false;    ///< True if error_estimate is valid
    double error_estimate = 0.0;        ///< Estimated error (optional)
    std::map<std::string, double> meta; ///< Additional info (e.g., Monte Carlo variance, seed)

    bool success = true;                ///< True if integration succeeded, false otherwise
};

} // namespace integ