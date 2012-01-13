set(Wobble_SRCS type.cpp identifier.cpp class.cpp project.cpp input.cpp output.cpp)


qt4_automoc(${Wobble_SRCS})
add_library(WobbleCore SHARED ${Wobble_SRCS})
target_link_libraries(WobbleCore ${QT_QTCORE_LIBRARY})
