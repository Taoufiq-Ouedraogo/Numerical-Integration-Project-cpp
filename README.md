# Integration Project

This project demonstrates a C++ integration library with a demo application.  
It uses **CMake** for building and supports outputting results to a CSV file.

---

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

---


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


---

## Documentation

The full API documentation is generated using **Doxygen**.

After generating the docs, open the following file in your browser:
`docs/html/index.html`

Or, if you are viewing this repository locally, you can open it directly:
`docs/html/index.html`

This documentation includes:
- Core abstractions (`Function`, `Solver`, `Domain2D`)
- All numerical integration methods (1D & 2D)
- Mathematical formulas and constraints