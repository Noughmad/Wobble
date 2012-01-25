set(Wobble_utils_SRCS
    templates.cpp 
)

add_definitions(-DMAKE_WOBBLE_UTILS_LIBRARY)

wobble_add_library(WobbleUtils ${Wobble_utils_SRCS})
target_link_libraries(WobbleUtils WobbleCore ${QT_QTCORE_LIBRARY})
install(TARGETS WobbleUtils EXPORT WobbleLibraryDepends ${INSTALL_TARGETS_DEFAULT_ARGS})

