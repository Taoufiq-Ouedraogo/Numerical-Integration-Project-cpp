# Integration Project

This project demonstrates a C++ integration library with a demo application.  
It uses **CMake** for building and supports outputting results to a CSV file.

---


<br>

## Project Structure


```python
├── apps/            # Demo applications
│   └── demo.cpp     # Main demo application
├── build/           # CMake build folder (ignored by Git)
├── docs/            # Doxygen documentation source
├── include/         # Header files
├── src/             # Source files
├── CMakeLists.txt
├── Doxyfile
├── README.md
└── .gitignore
```


Build Folder
```python
├── build/                      # CMake build folder (ignored by Git)
│   ├── cmake_install.cmake
│   ├── CMakeFiles
│   ├── Makefile
│   └── outputs                 # Generated CSV results 
│       └── results.csv
```


Include Directory (Headers)
```python
├── include/                  # Header files
│   ├── core/                 # Core abstractions
│   │   ├── Domain2D.hpp
│   │   ├── Function.hpp
│   │   ├── Function2D.hpp
│   │   ├── IntegrationResult.hpp
│   │   ├── Interval.hpp
│   │   └── Solver.hpp
│   ├── functions/            # 1D & 2D function implementations
│   │   ├── ExpXY2D.hpp
│   │   ├── InvSqrt.hpp
│   │   ├── LogX.hpp
│   │   ├── PolyX2Cos.hpp
│   │   ├── Power.hpp
│   │   ├── ProductXY2D.hpp
│   │   ├── SinXY2D.hpp
│   │   ├── SumSquaresXY2D.hpp
│   │   └── T2Transform.hpp
│   └── solvers/              # Integration solvers
│       ├── CompositeSimpson.hpp
│       ├── CompositeTrapezoid.hpp
│       ├── GaussLegendre.hpp
│       ├── GSLIntegrator.hpp
│       ├── MonteCarloUniform.hpp
│       └── NestedIntegral2D.hpp
```


Source Directory (Implementations)
```python
├── src/                      # Source files
│   ├── core/                 # Core class implementations
│   │   ├── Domain2D.cpp
│   │   └── Interval.cpp
│   └── solvers/              # Solver implementations
│       ├── CompositeSimpson.cpp
│       ├── CompositeTrapezoid.cpp
│       ├── GaussLegendre.cpp
│       ├── GSLIntegrator.cpp
│       ├── MonteCarloUniform.cpp
│       └── NestedIntegral2D.cpp
```


<br>


## Prerequisites

- C++17 compatible compiler
- [CMake](https://cmake.org/) installed
- macOS users: recommended to install CMake via Homebrew:

```bash
brew install cmake
```

You may have also to download GSL:
```bash
brew install gsl
```





<br>

## Build Instructions


1. Create and enter the build directory:
```bash
mkdir -p build
cd build
```

If the directory already exists, please remove it with:
```bash
rm -rf build
```


2. Configure the project with CMake:
```bash
cmake ..
```

3. Build the project:
```bash
cmake --build .
```

This will generate the `demo` executable inside the `build/` folder


4. Run Demo

From the `build/` folder, run:

```bash
./demo --output ../outputs/results.csv
```

The results will be saved in the `outputs/` directory.


<br>


## Documentation (Doxygen)

To generate the full API documentation:

1. Run Doxygen (at the project root) with the included Doxyfile:
```bash
doxygen Doxyfile
```

2. Open the documentation in your browser:
```bash
open docs/html/index.html      # macOS
xdg-open docs/html/index.html  # Linux
```

This documentation includes:
- Core abstractions (Function, Solver, Domain2D)
- All numerical integration methods (1D & 2D)
- Mathematical formulas and constraints

