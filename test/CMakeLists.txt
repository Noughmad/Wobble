
wobble_add_executable(plugintest plugintest.cpp)
target_link_libraries(plugintest WobbleCore ${QT_QTTEST_LIBRARY} ${QT_QTCORE_LIBRARY})
add_test(plugin plugintest)
