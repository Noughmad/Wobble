
set(Wobble_APP_SRCS main.cpp)

add_executable(wobble ${Wobble_APP_SRCS})
target_link_libraries(wobble WobbleCore ${QT_QTCORE_LIBRARY})
install(TARGETS wobble EXPORT WobbleLibraryDepends ${INSTALL_TARGETS_DEFAULT_ARGS})
