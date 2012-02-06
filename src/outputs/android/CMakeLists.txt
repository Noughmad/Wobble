set(Wobble_android_SRCS androidoutput.android)

wobble_add_library(WobbleAndroidOutput ${Wobble_android_SRCS})
target_link_libraries(WobbleAndroidOutput WobbleCore WobbleUtils ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})
install(TARGETS WobbleAndroidOutput ${INSTALL_PLUGINS_DEFAULT_ARGS})

install(FILES templates/CMakeLists.top templates/main.android templates/CMakeLists.src templates/class.h templates/class_p.h templates/class.android DESTINATION ${TEMPLATE_INSTALL_DIR}/android)