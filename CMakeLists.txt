project(Wobble)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(Doxygen)

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

find_package(YAML)
find_package(Grantlee)

if (Grantlee_FOUND)
    set(FILTER_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/filters)
    set(TEMPLATE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/templates)
    include(${Grantlee_USE_FILE})
endif()

include_directories(${QT_INCLUDES} ${Grantlee_INCLUDE_DIRS} ${CMAKE_CURRENT_BINARY_DIR} ${CMAKE_CURRENT_SOURCE_DIR} )

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

set(BIN_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(LIB_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/lib")


set(INSTALL_TARGETS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}" COMPONENT Devel )

set(INSTALL_PLUGINS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}/wobble"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}/wobble"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}/wobble" COMPONENT Devel )

set(Grantlee_DIR "grantlee/${Grantlee_VERSION_MAJOR}.${Grantlee_VERSION_MINOR}")

set(INSTALL_FILTERS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}/${Grantlee_DIR}"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}/${Grantlee_DIR}"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}/${Grantlee_DIR}" COMPONENT Devel )

set(CMAKE_INSTALL_RPATH "${LIB_INSTALL_DIR}")


# add a target to generate API documentation with Doxygen

add_subdirectory(src)
add_subdirectory(test)