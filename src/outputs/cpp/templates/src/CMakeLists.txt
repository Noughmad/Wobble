set({{ name }}_SRCS 
{% for file in sourceFiles %}
    file
{% endfor %}
)

{% if library %}
wobble_add_library({{ name }} ${{{ name }}_SRCS})
{% else %}
wobble_add_executable({{ name }} ${{{ name }}_SRCS})
{% endif %}
target_link_libraries({{ name }} ${QT_QTCORE_LIBRARY}{% for dep in dependencies %} dep.library{% endfor %})
