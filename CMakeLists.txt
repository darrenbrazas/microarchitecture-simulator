cmake_minimum_required(VERSION 3.16)
project(microarch_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Collect all source files
file(GLOB_RECURSE SOURCES "src/**/*.cpp")

# Main executable
add_executable(simulator main.cpp ${SOURCES})