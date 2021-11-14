cmake_minimum_required(VERSION 3.14)

set(PROJECT "dogCam")
project("${PROJECT}_Project" VERSION 0.0.1 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_TESTING       "Enable a Unit Testing build."          ON)
option(ENABLE_COVERAGE      "Enable a Code Coverage build."         OFF)
option(ENABLE_BENCHMARKS    "Enable a benchmark build."             ON)
option(ENABLE_CLANG_TIDY    "Enable a clang tidy checks."           OFF)
option(ENABLE_CPPCHECK      "Enable a cppcheck checks."             OFF)
option(ENABLE_LTO           "Enable Link Time Optimization (LTO)."  OFF)
option(ENABLE_CCACHE        "Enable the usage of Ccache."           OFF)

# Project/Library Names
set(LIBRARY_NAME    ${PROJECT}_Lib)
set(EXECUTABLE_NAME ${PROJECT}_Executable)

# Add first-party libraries
add_subdirectory(src)

# Add executables
add_subdirectory(app)

