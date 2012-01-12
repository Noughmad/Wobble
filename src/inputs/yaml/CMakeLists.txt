set(Wobble_yaml_SRCS yamlinput.cpp)

qt4_automoc(${Wobble_yaml_SRCS})
add_library(WobbleYamlInput SHARED ${Wobble_yaml_SRCS})
target_link_libraries(WobbleYamlInput WobbleCore ${QT_QTCORE_LIBRARY})
