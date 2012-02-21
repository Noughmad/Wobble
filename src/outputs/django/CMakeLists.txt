set(Wobble_django_SRCS 
  djangooutput.cpp
  djangowriter.cpp
  )

wobble_add_library(WobbleDjangoOutput ${Wobble_django_SRCS})
target_link_libraries(WobbleDjangoOutput WobbleCore WobbleUtils ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})
install(TARGETS WobbleDjangoOutput ${INSTALL_PLUGINS_DEFAULT_ARGS})

install(FILES templates/models.py templates/views.py DESTINATION ${TEMPLATE_INSTALL_DIR}/cpp)

add_subdirectory(filters)
