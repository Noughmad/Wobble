set(Wobble_SRCS common.cpp
    type.cpp 
    identifier.cpp
    class.cpp
    view.cpp 
    variable.cpp
    project.cpp
    input.cpp
    output.cpp
)

add_definitions(-DMAKE_WOBBLE_LIBRARY)
configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h")

wobble_add_library(WobbleCore ${Wobble_SRCS})
target_link_libraries(WobbleCore ${QT_QTCORE_LIBRARY})
install(TARGETS WobbleCore ${INSTALL_TARGETS_DEFAULT_ARGS})
