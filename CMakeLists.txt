cmake_minimum_required(VERSION 3.20)
project(system-monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(system-monitor
    src/main.cpp
    src/ResourceMonitor.cpp
)

set_target_properties(system-monitor PROPERTIES
    WIN32_EXECUTABLE TRUE
)
