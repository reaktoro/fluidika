# Set cmake version requirement
cmake_minimum_required(VERSION 3.1)

# Set the name of the project
project(Fluidik VERSION 0.1 LANGUAGES CXX)

# The a brief description of the project
set(PROJECT_BRIEF "A scientific C++ library for calculation of thermophysical properties of fluids")

# Set the cmake module path of the project
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include the cmake variables with values for installation directories
include(GNUInstallDirs)

# Set the output directories of the built libraries and binaries
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})

# Define which types of libraries to build
option(BUILD_SHARED_LIBS "Build shared libraries." ON)
option(BUILD_STATIC_LIBS "Build static libraries." ON)

# Fluidik currently is not setup to produce a dynamic library using MSVC, only static
if(${CMAKE_CXX_COMPILER_ID} STREQUAL MSVC)
    set(BUILD_SHARED_LIBS OFF)
endif()

# Set warning level during compilation
if(MSVC)
    add_compile_options(/W4) # warning level 4 in visual studio 
else()
    add_compile_options(-Wall -Wextra -pedantic) # all warnings for gcc and clang
endif()

# Build the dependencies of the project
add_subdirectory(deps)

# Build the C++ library 
add_subdirectory(Fluidik)

# Build the documentation
#add_subdirectory(doc EXCLUDE_FROM_ALL)
