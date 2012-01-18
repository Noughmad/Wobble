set(Cpp_filters_SRCS cpplibrary.cpp)

grantlee_add_plugin(grantlee_cppfilters cpplibrary)

install(TARGETS grantlee_cppfilters ${INSTALL_FILTERS_DEFAULT_ARGS})
