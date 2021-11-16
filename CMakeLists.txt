cmake_minimum_required(VERSION 3.14)

set(PROJECT "dogCam")
project("${PROJECT}_Project" VERSION 0.0.1 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              11)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS      "Enable to add warnings to a target."   ON)
option(ENABLE_CROSSCOMPILING_RPI0 "Enable Cross compiling fpr armv6." ON)

# option(ENABLE_TESTING       "Enable a Unit Testing build."          ON)
# option(ENABLE_COVERAGE      "Enable a Code Coverage build."         OFF)
# option(ENABLE_BENCHMARKS    "Enable a benchmark build."             ON)
# option(ENABLE_CLANG_TIDY    "Enable a clang tidy checks."           OFF)
# option(ENABLE_CPPCHECK      "Enable a cppcheck checks."             OFF)
# option(ENABLE_LTO           "Enable Link Time Optimization (LTO)."  OFF)
# option(ENABLE_CCACHE        "Enable the usage of Ccache."           OFF)

# if(ENABLE_CROSSCOMPILING_RPI0)
#     message("Corss Compiling for RPI0..")
#     # set(CMAKE_TOOLCHAIN_FILE "/cmake/toolchain-rpi.cmake")
# endif(ENABLE_CROSSCOMPILING_RPI0)

if(CMAKE_CROSSCOMPILING)
    message("Enable the Cross Compiler for RPI0..")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv6")
endif()

# Project/Library Names
set(LIBRARY_NAME    ${PROJECT}_Lib)
set(EXECUTABLE_NAME ${PROJECT}_Executable)

# Add first-party libraries
add_subdirectory(src)

# Add executables
add_subdirectory(app)