set (CMAKE_CXX_STANDARD 20)
cmake_minimum_required(VERSION 3.10.0)

project(EMBSYS VERSION 1.0)

find_package(Catch2 REQUIRED)
find_package(GSL REQUIRED)

include(CTest)
include(Catch)


add_subdirectory(project_2)


