set(Wobble_debug_SRCS debugoutput.cpp)

wobble_add_library(WobbleDebugOutput SHARED ${Wobble_debug_SRCS})
target_link_libraries(WobbleDebugOutput WobbleCore ${QT_QTCORE_LIBRARY})

