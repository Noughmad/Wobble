set(Wobble_cpp_SRCS cppoutput.cpp)

wobble_add_library(WobbleCppOutput SHARED ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore ${QT_QTCORE_LIBRARY})
