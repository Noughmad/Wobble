"""
    {{ license }}
"""

from django.db import models

{% for cls in classes %}
class {{ cls.name }}({% for s in cls.superclasses %}s.name{% empty %}models.Model{% endfor %}):
    {% for p in cls.properties %}
    {{ p.name }} = {{ p|field_declaration }}
    {% endfor %}
{% endfor %}
