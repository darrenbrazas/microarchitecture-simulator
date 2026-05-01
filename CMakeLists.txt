cmake_minimum_required(VERSION 3.16)
project(microarch_simulator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include headers
include_directories(include)

# Explicitly list source files
set(SOURCES
    src/isa/decode.cpp
    src/cpu/single_cycle.cpp
)

# Main executable
add_executable(simulator main.cpp ${SOURCES})