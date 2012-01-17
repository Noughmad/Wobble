set(Wobble_django_SRCS djangooutput.cpp)

wobble_add_library(WobbleDjangoOutput ${Wobble_django_SRCS})
target_link_libraries(WobbleDjangoOutput WobbleCore ${QT_QTCORE_LIBRARY} ${Grantlee_CORE_LIBRARIES})

install(FILES templates/models.py DESTINATION share/templates/django)
