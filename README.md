# Libpp - Generic C++ library for path planning

[![Ubuntu CI](https://github.com/KeeJin/libpp/actions/workflows/ubuntu-ci.yml/badge.svg)](https://github.com/KeeJin/libpp/actions/workflows/ubuntu-ci.yml)

## Compilation Instructions

1. Install Conan 2.0 within a python venv using ./scripts/setup-conan-with-venv.sh
2. Source the virtual environment with:

```
    source ./conan_venv/bin/activate
```

3. Install conan dependencies and invoke cmake preset to use conan toolchain

```
    conan install . --build=missing -r conancenter
    cmake --preset conan-release
```

4. Compile the code (tests enabled by default)
```
    cmake --build --preset conan-release
```
