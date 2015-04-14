#
# Project properties 
#
  
project(ObjectTrackingForVideo)
cmake_minimum_required( VERSION 2.8 )

#
# Project options
#

#
# Project directories
#
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src" )

#OpenCV
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_DIRS})

add_subdirectory(${SRC_DIR})
include_directories(${SRC_DIR})

#include source file in all folder
set(PROJECT_SRCS
    ${TOP_SRCS}
    )

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
