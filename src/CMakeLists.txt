file( GLOB_RECURSE TOP_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/*.c
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
)

set( TOP_SRCS
    ${TOP_SRCS}
    PARENT_SCOPE
)

