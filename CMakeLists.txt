cmake_minimum_required(VERSION 3.20)
project(Project)

set(CMAKE_CXX_STANDARD 14)
set(GRAPHLIB_DIR ${CMAKE_SOURCE_DIR}/lib/GraphLib)

add_subdirectory(GraphLibUse)
add_subdirectory(unit-tests)
add_subdirectory(lib/googletest)
add_subdirectory(${GRAPHLIB_DIR})

file(GLOB GLSOURCES ${GRAPHLIB_DIR}/*.h ${GRAPHLIB_DIR}/*.cpp)
file(GLOB HEADER_FILES include/*.h)
file(GLOB SOURCE_FILES include/*.cpp)

add_executable(project ${HEADER_FILES} ${GLSOURCES} ${SOURCE_FILES} main.cpp)

target_include_directories(project PUBLIC ${GRAPHLIB_DIR})
target_include_directories(project PUBLIC include)
