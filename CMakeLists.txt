cmake_minimum_required(VERSION 3.14)
project(backtester)

# Set pybind11_DIR to the path returned by `python -m pybind11 --cmakedir`
set(pybind11_DIR "../proton/.venv/Lib/site-packages/pybind11/share/cmake/pybind11")

find_package(pybind11 REQUIRED)

pybind11_add_module(backtester_module src/main.cpp)

set_target_properties(backtester_module PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}
)
