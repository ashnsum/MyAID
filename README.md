# MyAID

A simple C++ project that prints a greeting message.

## Prerequisites

- **CMake**: Version 3.10 or higher. Download from [cmake.org](https://cmake.org/download/).
- **MinGW-w64 GCC**: C++ compiler. Install via winget:
  ```
  winget install --id BrechtSanders.WinLibs.POSIX.UCRT --accept-source-agreements --accept-package-agreements
  ```
  Ensure the MinGW bin directory is in your PATH (it should be added automatically).

## Project Structure

```
MyAID/
├── CMakeLists.txt          # CMake configuration
├── .clang-format           # Clang-format configuration for code style
├── app/
│   └── Engine/
│       ├── main.cpp        # Main source file
│       └── BUILD           # Bazel build file (unused)
├── build/                  # Build directory (generated)
└── .vscode/                # VS Code configurations
    ├── settings.json
    ├── tasks.json
    ├── launch.json
    └── cmake-kits.json
```

## Building the Project

### Option 1: Using VS Code (Recommended)

1. Open the project in VS Code.
2. Ensure CMake Tools extension is installed.
3. Select the "WinLibs GCC" kit: `CMake: Select a Kit` > `WinLibs GCC`.
4. Build: Press `Ctrl+Shift+B` or use `Terminal > Run Task > Run myapp`.
5. The executable `myapp.exe` will be in the `build/` directory.

### Option 2: Manual Build

1. Open PowerShell or Command Prompt in the project root.
2. Create build directory:
   ```
   mkdir build
   cd build
   ```
3. Configure with CMake:
   ```
   cmake -G "MinGW Makefiles" ..
   ```
4. Build:
   ```
   cmake --build .
   ```
5. Run:
   ```
   ./myapp.exe
   ```

## Running the Project

- **From VS Code**: Press `F5` to debug, or `Ctrl+Shift+B` to run.
- **Manually**: `./build/myapp.exe`

## VS Code Configurations

The `.vscode/` folder contains:
- `settings.json`: CMake source and build directories, auto-formatting on save, and clang-format settings.
- `tasks.json`: Build and run tasks.
- `launch.json`: Debug configuration with GDB.
- `cmake-kits.json`: GCC kit definition.

The project also includes `.clang-format` for consistent code formatting with 80-character line limits.

These ensure VS Code can build, debug, and format the project seamlessly.

## Notes

- The project uses CMake for cross-platform builds.
- MinGW provides the GCC compiler for Windows.
- If you encounter PATH issues, ensure MinGW bin is in your user PATH (check with `[Environment]::GetEnvironmentVariable("Path", "User")`).