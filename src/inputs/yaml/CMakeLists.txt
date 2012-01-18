set(Wobble_yaml_SRCS yamlinput.cpp)

wobble_add_library(WobbleYamlInput ${Wobble_yaml_SRCS})
target_link_libraries(WobbleYamlInput WobbleCore ${QT_QTCORE_LIBRARY} ${YAML_LIBRARIES})
install(TARGETS WobbleYamlInput ${INSTALL_PLUGINS_DEFAULT_ARGS})
