set(Wobble_debug_SRCS debugoutput.cpp)

wobble_add_library(WobbleDebugOutput ${Wobble_debug_SRCS})
target_link_libraries(WobbleDebugOutput WobbleCore ${QT_QTCORE_LIBRARY})
install(TARGETS WobbleDebugOutput ${INSTALL_PLUGINS_DEFAULT_ARGS})

