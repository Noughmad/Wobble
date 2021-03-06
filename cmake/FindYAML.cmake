# - Find yaml-cpp
# Find the yaml-cpp library
#
#  This module defines the following variables:
#     YAML_FOUND       - True if YAML_INCLUDE_DIR & YAML_LIBRARY are found
#     YAML_LIBRARIES   - Set when YAML_LIBRARY is found
#     YAML_INCLUDE_DIRS - Set when YAML_INCLUDE_DIR is found
#
#     YAML_INCLUDE_DIR - where to find asoundlib.h, etc.
#     YAML_LIBRARY     - the asound library
#

#=============================================================================
# Copyright 2009 Kitware, Inc.
# Copyright 2009 Philip Lowman <philip@yhbt.com>
#
# Distributed under the OSI-approved BSD License (the "License");
# see accompanying file Copyright.txt for details.
#
# This software is distributed WITHOUT ANY WARRANTY; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the License for more information.
#=============================================================================
# (To distribute this file outside of CMake, substitute the full
#  License text for the above reference.)

find_path(YAML_INCLUDE_DIR NAMES node.h
          PATH_SUFFIXES yaml-cpp
          DOC "The YAML (yaml-cpp) include directory"
)

find_library(YAML_LIBRARY NAMES yaml-cpp
          DOC "The YAML (yaml-cpp) library"
)

# handle the QUIETLY and REQUIRED arguments and set YAML_FOUND to TRUE if 
# all listed variables are TRUE
include(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(YAML DEFAULT_MSG YAML_LIBRARY YAML_INCLUDE_DIR)

if(YAML_FOUND)
  set( YAML_LIBRARIES ${YAML_LIBRARY} )
  set( YAML_INCLUDE_DIRS ${YAML_INCLUDE_DIR} )
endif()

mark_as_advanced(YAML_INCLUDE_DIR YAML_LIBRARY)
