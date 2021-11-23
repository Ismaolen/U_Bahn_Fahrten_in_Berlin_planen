cmake_minimum_required(VERSION 3.20)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set(GRAPHLIB_DIR ${CMAKE_SOURCE_DIR}/lib/GraphLib)

add_subdirectory(unit-tests)
add_subdirectory(lib/googletest)
add_subdirectory(${GRAPHLIB_DIR})

add_executable(project ${SOURCES} main.cpp)

target_include_directories(project PUBLIC ${GRAPHLIB_DIR})

