# ./CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(cpp_integration LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library
add_library(integration
    src/core/Interval.cpp
    src/core/Domain2D.cpp    

    src/solvers/CompositeTrapezoid.cpp
    src/solvers/CompositeSimpson.cpp
    src/solvers/MonteCarloUniform.cpp
    src/solvers/GaussLegendre.cpp
    src/solvers/GSLIntegrator.cpp  
    src/solvers/NestedIntegral2D.cpp
)

target_include_directories(integration
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_options(integration PRIVATE -Wall -Wextra -Wpedantic)

# --- GSL setup ---
find_path(GSL_INCLUDE_DIR gsl/gsl_integration.h PATHS /opt/homebrew/include)
find_library(GSL_LIBRARY NAMES gsl PATHS /opt/homebrew/lib)
find_library(GSLCBLAS_LIBRARY NAMES gslcblas PATHS /opt/homebrew/lib)

if(NOT GSL_INCLUDE_DIR OR NOT GSL_LIBRARY OR NOT GSLCBLAS_LIBRARY)
    message(FATAL_ERROR "GSL not found! Make sure it is installed and the paths are correct.")
endif()

message(STATUS "GSL include dir: ${GSL_INCLUDE_DIR}")
message(STATUS "GSL library: ${GSL_LIBRARY}")
message(STATUS "GSL CBLAS library: ${GSLCBLAS_LIBRARY}")

target_include_directories(integration
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
    PUBLIC ${GSL_INCLUDE_DIR}    # <<< add this
)
target_link_libraries(integration PRIVATE ${GSL_LIBRARY} ${GSLCBLAS_LIBRARY})

# Demo executable
add_executable(demo apps/demo.cpp)
target_link_libraries(demo PRIVATE integration)
target_include_directories(demo PRIVATE ${CMAKE_SOURCE_DIR}/src)