project(Wobble)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(Doxygen)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

# add a target to generate API documentation with Doxygen

add_subdirectory(src)