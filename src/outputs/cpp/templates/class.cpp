{% load grantlee_cppfilters %}
{{ license }}

#include "{{ name|lower }}.h"
{% if dpointer %}
#include "{{ name|lower }}_p.h"
{% endif %}

{% if nameSpace %}using namespace nameSpace;{% endif %}

{% if dpointer %}

{{ name }}Private::{{ name }}Private()
{% templatetag openbrace %}
{% templatetag closebrace %}

{{ name }}Private::~{{ name }}Private()
{% templatetag openbrace %} 
{% templatetag closebrace %}

{% endif %}

{{ name }}::{{ name }}(QObject* parent = 0) : QObject(parent)
{% templatetag openbrace %}
    
{% templatetag closebrace %}

virtual ~{{ name }}()
{% templatetag openbrace %}
    
{% templatetag closebrace %}

{% for p in properties %}
{{ p.type|return_arg }} {{ name }}::{{ p|getter_name }}()
{% templatetag openbrace %}    
    {% if dpointer %}
    Q_D(const {{ p.name }});
    return d->{{ p.name }};
    {% endif %}
    return m_{{ p.name }};
{% templatetag closebrace %}

void {{ name }}::{{ p|setter_name }}({{ p.type|pass_arg }} {{ p.name }})
{% templatetag openbrace %}    
    {% if dpointer %}
    Q_D({{ p.name }});
    d->{{ p.name }} = {{ p.name }};
    {% endif %}
    m_{{ p.name }} = {{ p.name }};
{% templatetag closebrace %}
{% endfor %}
