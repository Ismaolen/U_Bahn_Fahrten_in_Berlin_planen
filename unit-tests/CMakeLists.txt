project(unit-tests)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB GLSOURCES ${GRAPHLIB_DIR}/*.h ${GRAPHLIB_DIR}/*.cpp)
#  ${GRAPHLIB_DIR}/edge.h ${GRAPHLIB_DIR}/node.h ${GRAPHLIB_DIR}/graph.h
# ${GRAPHLIB_DIR}/edge.cpp ${GRAPHLIB_DIR}/node.cpp ${GRAPHLIB_DIR}/graph.cpp
set(HEADER_FILES pch.h)
set(SOURCE_FILES pch.cpp  main.cpp)

add_executable(unit-tests ${HEADER_FILES} ${GLSOURCES} ${SOURCE_FILES})

target_include_directories(unit-tests PUBLIC ../lib/GraphLib)
target_link_libraries(unit-tests gtest gtest_main)
