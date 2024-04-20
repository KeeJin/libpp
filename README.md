# Libpp - Generic C++ library for path planning algorithms  

[![Ubuntu CI](https://github.com/KeeJin/libpp/actions/workflows/ubuntu-ci.yml/badge.svg)](https://github.com/KeeJin/libpp/actions/workflows/ubuntu-ci.yml)

## Compilation Instructions

<!-- 1. Install Conan 2.0 within a python venv using ./scripts/setup-conan-with-venv.sh
2. Source the virtual environment with:
    ```
        source ./conan_venv/bin/activate
    ``` -->

### Compile with tests from root project directory:

    ```
        mkdir -p build
        conan install . --output-folder=build --build=missing
        cd build && cmake .. && make -j
    ```
