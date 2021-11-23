project(graphlib-use)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB GLSOURCES ${GRAPHLIB_DIR}/*.h ${GRAPHLIB_DIR}/*.cpp)
set(HEADER_FILES )
set(SOURCE_FILES main.cpp)

add_executable(graphlib-use ${HEADER_FILES} ${GLSOURCES} ${SOURCE_FILES})

target_include_directories(graphlib-use PUBLIC ../lib/GraphLib)
target_link_libraries(graphlib-use gtest gtest_main)