cmake_minimum_required(VERSION 3.10.0)

# project(EMBSYS VERSION 1.0)
project(P2)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
# set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_BUILD_TYPE Debug)

find_package(Catch2 3 REQUIRED)

include(CTest)
include(Catch)

add_subdirectory(project_2)


