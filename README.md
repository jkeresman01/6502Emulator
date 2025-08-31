<div align="center">

  <h1>  6502 emulator. </h1>
  <h6> =====    This is custom 6502 emulator    ===== </h6>

![C++](https://img.shields.io/badge/C++-blue?style=for-the-badge&logo=c%2B%2B)
![Work In Progress](https://img.shields.io/badge/Work%20In%20Progress-orange?style=for-the-badge)

</div>

<img width="1452" height="957" alt="image" src="https://github.com/user-attachments/assets/121125ae-10ac-40d2-9f08-3892e88a8f28" />

## Disclaimer ##

> **⚠️ Warning**  
> - This project is still **work in progress**.
> - Most of the remaing work is to be done on the assembler and dissasembler
> - Contributions, bug reports, and suggestions are welcome.

## Project structure ##

```cpp

emulator-application/   # Main application (entry point, app glue)
├── include/
├── src/
└── tests/

emulator-components/    # UI components (Editor, LEDs, PixelDisplay, etc.)
├── include/
├── src/
└── tests/

emulator-core/          # Core 6502 emulation (CPU, Memory, Assembler, etc.)
├── include/
├── src/
└── tests/

emulator-shared/        # Shared infrastructure (Logger, Assert, etc.)
├── include/
├── src/
└── tests/

emulator-utilities/     # Utility functions (Colors, Program helpers, Random)
├── include/
├── src/
└── tests/
```

## Documentation ##

[Doxygen documentation](https://jkeresman01.github.io/6502Emulator/)

## Build ##

### Get the code ###

```bash
git clone --recursive-submodule https://github.com/jkeresman01/6502Emulator/
cd 6502Emulator

# If you forgot --recurse-submodules:
git submodule update --init --recursive

```

### Configure ###

Top-level options (all optional):

* BUILD_TESTING — build unit tests (default: ON)

* ENABLE_SANITIZERS — enable ASan/UBSan (default: OFF)

* ENABLE_WARNINGS_AS_ERRORS — treat warnings as errors (default: OFF)



```bash
cmake -S . -B build \
  -DBUILD_TESTING=ON \
  -DENABLE_SANITIZERS=OFF \
  -DENABLE_WARNINGS_AS_ERRORS=OFF
```

> **Notes**  
> - **OpenGL**: The project prefers GLVND; legacy warnings are silenced by CMake policy in the project.  
> - **Doxygen**: If you don’t have ≥ 1.9.8, you’ll see a message; docs are optional and won’t block the build.


### Build ####

```bash
cmake --build build -j"$(nproc)"
```
### Run ###

```bash
./build/bin/6502EmulatorApp
```

### Run tests ###

```bash
ctest --test-dir build --output-on-failure
# or run individual test binaries:
./build/emulator-core/emulator_core_tests
./build/emulator-utilities/emulator_utilities_tests
# (an app test target may appear if tests exist in emulator-application/tests)
```
