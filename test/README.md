## How to build?

### Using CMake (Recommended)

1. Install [CMake](https://cmake.org/download/) (version 3.14 or higher)
2. Build the project:
   ```bash
   cd test
   mkdir build
   cd build
   cmake ..
   cmake --build .
   ```
3. Run tests:
   ```bash
   # Debug build
   ./Debug/interval_test.exe
   
   # Or Release build
   cmake --build . --config Release
   ./Release/interval_test.exe
   ```

The CMake build automatically downloads and configures Google Test, no manual installation required.
