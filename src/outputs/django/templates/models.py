{% load grantlee_djangofilters %}
"""

    {{ license }}
"""

from django.db import models

{% for cls in classes %}
class {{ cls.name }}({% for s in cls.superclasses %}{{ s.name }}{% empty %}models.Model{% endfor %}):
{% for p in cls.properties %}
    {{ p.name }} = {{ p|field_declaration }}
{% endfor %}
{% for f in cls.methods %}
    def {{ f.name }}({% for a in f.arguments %}{{ a.name }}, {% endfor %}):
        # TODO: Implement the method
        {% if f.returnType %}
        # Should return a {{ f.returnType }}. 
        {% endif %}
        pass
{% endfor %}
{% endfor %}
