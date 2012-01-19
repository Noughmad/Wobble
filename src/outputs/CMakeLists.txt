
if (BUILD_CPP_OUTPUT)
    add_subdirectory(cpp)
endif()

if (BUILD_DJANGO_OUTPUT)
    add_subdirectory(django)
endif()

if (BUILD_DEBUG_OUTPUT)
    add_subdirectory(debug)
endif()