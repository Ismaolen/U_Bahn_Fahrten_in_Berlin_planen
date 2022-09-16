project(unit-tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR})

file(GLOB GLSOURCES ${GRAPHLIB_DIR}/*.h ${GRAPHLIB_DIR}/*.cpp)
file(GLOB PSOURCES ${CMAKE_SOURCE_DIR}/include/*.h ${CMAKE_SOURCE_DIR}/include/*.cpp)
set(HEADER_FILES pch.h)
set(SOURCE_FILES pch.cpp  main.cpp)

add_executable(unit-tests ${PSOURCES} ${HEADER_FILES} ${GLSOURCES} ${SOURCE_FILES})

target_include_directories(unit-tests PUBLIC ../lib/GraphLib)
target_link_libraries(unit-tests gtest gtest_main)
