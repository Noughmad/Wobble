set(Wobble_cpp_SRCS cppoutput.cpp)

wobble_add_library(WobbleCppOutput ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})

install(FILES templates/CMakeLists.txt templates/src/main.cpp templates/src/CMakeLists.txt DESTINATION share/templates/cpp)

add_subdirectory(filters)