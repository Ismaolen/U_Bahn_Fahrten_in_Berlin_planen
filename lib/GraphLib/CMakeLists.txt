project(graphlib)

set(HEADER_FILES edge.h graph.h node.h)
set(SOURCE_FILES edge.cpp graph.cpp node.cpp)

add_library(graphlib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)
