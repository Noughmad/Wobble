{% load grantlee_djangofilters %}
"""
    {{ license }}
"""

from django.views.generic import DetailView, ListView, View

{% for view in views %}
class {{ view.name }}(DetailView):{% for q in view.queries %}
    queryset = {{ q|queryset }}{% endfor %}
{% endfor %}