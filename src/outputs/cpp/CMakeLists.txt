set(Wobble_cpp_SRCS cppoutput.cpp)

qt4_automoc(${Wobble_cpp_SRCS})
add_library(WobbleCppOutput SHARED ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore ${QT_QTCORE_LIBRARY})
