cmake_minimum_required(VERSION 3.24)
project("IMAC_TD5")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

# Exécutables
add_executable(exo1 src/exo1/main.cpp)
add_executable(exo2 src/exo2/main.cpp)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/input_guard_patrol.txt" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")