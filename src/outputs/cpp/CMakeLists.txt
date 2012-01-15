set(Wobble_cpp_SRCS cppoutput.cpp)

wobble_add_library(WobbleCppOutput ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})

install(FILES templates/CMakeLists.txt template/main.cpp DESTINATION share/templates/cpp)
