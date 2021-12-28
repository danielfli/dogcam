cmake_minimum_required(VERSION 3.14)

set(PROJECT "dogcam")
project("${PROJECT}_Project" VERSION 0.0.1 LANGUAGES CXX)

# Global CMake variables are set here
set(CMAKE_CXX_STANDARD              17)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS   ON)

# Options
option(ENABLE_WARNINGS              "Enable to add warnings to a target."   ON)
option(ENABLE_CROSSCOMPILING_RPI0   "Enable Cross compiling for Pi Zero arch = armv6." ON)
option(ENABLE_TESTING               "Enable a Unit Testing build."          ON)

# Cross Compiling for Pi zero architecture 
if(CMAKE_CROSSCOMPILING AND ENABLE_CROSSCOMPILING_RPI0)
    message("Enable the Cross Compiler for RPI0..")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=armv6")
endif()

# Project/Library Names
set(LIBRARY_NAME    ${PROJECT}_Lib)
set(EXECUTABLE_NAME ${PROJECT}_Exe)

# Add conan Library
# include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
# conan_basic_setup()

# Add external Projects 
#add_subdirectory(external)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBCAMERA REQUIRED libcamera)
message(STATUS "libcamera library found:")
message(STATUS "    version: ${LIBCAMERA_VERSION}")
message(STATUS "    libraries: ${LIBCAMERA_LINK_LIBRARIES}")
message(STATUS "    include path: ${LIBCAMERA_INCLUDE_DIRS}")
include_directories(${CMAKE_SOURCE_DIR} ${LIBCAMERA_INCLUDE_DIRS})

# Add first-party libraries
add_subdirectory(src)

# Add GTest
if(ENABLE_TESTING)    
    add_subdirectory(tests)
endif() 

# Add executables
add_subdirectory(app)
