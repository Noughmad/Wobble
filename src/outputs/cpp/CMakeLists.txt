set(Wobble_cpp_SRCS cppoutput.cpp)

wobble_add_library(WobbleCppOutput ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})
install(TARGETS WobbleCppOutput ${INSTALL_PLUGINS_DEFAULT_ARGS})

install(FILES templates/CMakeLists.top templates/main.cpp templates/CMakeLists.src templates/class.h DESTINATION share/templates/cpp)

add_subdirectory(filters)