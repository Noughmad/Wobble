set(Wobble_cpp_SRCS cppoutput.cpp)

wobble_add_library(WobbleCppOutput ${Wobble_cpp_SRCS})
target_link_libraries(WobbleCppOutput WobbleCore WobbleUtils ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})
install(TARGETS WobbleCppOutput ${INSTALL_PLUGINS_DEFAULT_ARGS})

install(FILES templates/CMakeLists.top templates/main.cpp templates/CMakeLists.src templates/class.h templates/class_p.h templates/class.cpp DESTINATION ${TEMPLATE_INSTALL_DIR}/cpp)

add_subdirectory(filters)