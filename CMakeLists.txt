project(Wobble)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)
find_package(Doxygen)

set(Wobble_MAJOR_VERSION 0)
set(Wobble_MINOR_VERSION 1)
set(Wobble_PATCH_VERSION 0)
set(Wobble_VERSION
  ${Wobble_MAJOR_VERSION}.${Wobble_MINOR_VERSION}.${Wobble_PATCH_VERSION})

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake ${CMAKE_MODULE_PATH})

option (BUILD_CORE "Build the core Wobble library" TRUE)
option (BUILD_UTILS "Build the Wobble utilities library" TRUE)
option (BUILD_YAML_INPUT "Build the YAML input plugin" TRUE)
option (BUILD_CPP_OUTPUT "Build the C++/Qt output plugin" TRUE)
option (BUILD_DJANGO_OUTPUT "Build the Python/Django output plugin" TRUE)
option (BUILD_DEBUG_OUTPUT "Build the debug output plugin" TRUE)
option (BUILD_EXE "Build the Wobble executable" TRUE)

enable_testing()

if (BUILD_YAML_INPUT)
    find_package(YAML)
endif()

if (BUILD_CPP_OUTPUT OR BUILD_DJANGO_OUTPUT)
    find_package(Grantlee)
endif()

if (Grantlee_FOUND)
    set(Grantlee_DIR "grantlee/${Grantlee_VERSION_MAJOR}.${Grantlee_VERSION_MINOR}")
    set(FILTER_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib/${Grantlee_DIR})
    set(TEMPLATE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/templates)
    include(${Grantlee_USE_FILE})
else (Grantlee_FOUND)
    set(BUILD_CPP_OUTPUT FALSE)
    set(BUILD_DJANGO_OUTPUT FALSE)
endif(Grantlee_FOUND)

if (NOT YAML_FOUND)
    set(BUILD_YAML_INPUT FALSE)
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

set(PLUGIN_INSTALL_DIR "${LIB_INSTALL_DIR}/wobble")
set(INSTALL_CMAKE_DIR "${LIB_INSTALL_DIR}/cmake/Wobble")
set(INCLUDE_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/include/Wobble")


set(INSTALL_TARGETS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}" COMPONENT Devel )

set(INSTALL_PLUGINS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}/wobble"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}/wobble"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}/wobble" COMPONENT Devel )

set(INSTALL_FILTERS_DEFAULT_ARGS  RUNTIME DESTINATION "${BIN_INSTALL_DIR}/${Grantlee_DIR}"
                                  LIBRARY DESTINATION "${LIB_INSTALL_DIR}/${Grantlee_DIR}"
                                  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}/${Grantlee_DIR}" COMPONENT Devel )

set(CMAKE_INSTALL_RPATH "${LIB_INSTALL_DIR}")

if (${CMAKE_CXX_COMPILER_ID} MATCHES GNU)
    set( CMAKE_CXX_FLAGS_DEBUG "-O2 -Wall -g -pedantic" )
    set( CMAKE_CXX_FLAGS_RELEASE "-Os -Wall" )
endif()

add_subdirectory(src)
add_subdirectory(test)

export(TARGETS WobbleCore WobbleUtils wobble
  FILE "${PROJECT_BINARY_DIR}/WobbleLibraryDepends.cmake")

export(PACKAGE Wobble)

# Create the WobbleConfig.cmake and WobbleConfigVersion files
file(RELATIVE_PATH CONF_REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INCLUDE_INSTALL_DIR}")

configure_file(WobbleConfig.cmake.in
  "${PROJECT_BINARY_DIR}/WobbleConfig.cmake" @ONLY)
configure_file(WobbleConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/WobbleConfigVersion.cmake" @ONLY)

# Install the export set for use with the install-tree
install(EXPORT WobbleLibraryDepends
    DESTINATION "${INSTALL_CMAKE_DIR}"
    COMPONENT dev)

install(FILES
  "${PROJECT_BINARY_DIR}/WobbleConfig.cmake"
  "${PROJECT_BINARY_DIR}/WobbleConfigVersion.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}"
)