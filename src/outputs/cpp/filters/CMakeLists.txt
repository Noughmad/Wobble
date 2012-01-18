set(Cpp_filters_SRCS cpplibrary.cpp)

wobble_add_library(WobbleCppFilters ${Cpp_filters_SRCS})
target_link_libraries(WobbleCppFilters WobbleCore ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})
install(TARGETS WobbleCppFilters DESTINATION ${FILTER_INSTALL_DIR})
