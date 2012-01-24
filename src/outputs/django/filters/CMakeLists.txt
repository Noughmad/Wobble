set(Django_filters_SRCS djangofilters.cpp)

grantlee_add_plugin(grantlee_djangofilters djangofilters)

install(TARGETS grantlee_djangofilters ${INSTALL_FILTERS_DEFAULT_ARGS})
