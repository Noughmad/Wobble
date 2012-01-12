project(Wobble)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(Wobble_SRCS Wobble.cpp main.cpp)
qt4_automoc(${Wobble_SRCS})
add_executable(Wobble ${Wobble_SRCS})
target_link_libraries(Wobble ${QT_QTCORE_LIBRARY})
