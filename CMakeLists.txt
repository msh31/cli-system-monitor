cmake_minimum_required(VERSION 3.20)
project(system-monitor)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(${CMAKE_SOURCE_DIR}/includes)

add_executable(system-monitor
    src/main.cpp
    src/ResourceMonitor.cpp
)

target_link_libraries(system-monitor psapi pdh)
