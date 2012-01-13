project(Wobble)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(Doxygen)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(YAML)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

macro(wobble_add_executable _target_NAME)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    qt4_automoc(${ARGN})
    add_executable(${_target_NAME} ${ARGN} )
endmacro(wobble_add_executable)

macro(wobble_add_library _target_NAME)
    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    qt4_automoc(${ARGN})
    add_library(${_target_NAME} SHARED ${ARGN} )
endmacro(wobble_add_library)

# add a target to generate API documentation with Doxygen

add_subdirectory(src)
add_subdirectory(test)