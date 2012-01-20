{% load grantlee_cppfilters %}
{{ license }}

#include "{{ name|lower }}.h"
{% if dpointer %}
#include "{{ name|lower }}_p.h"
{% endif %}

{% if nameSpace %}using namespace nameSpace;{% endif %}

{% if dpointer %}
{{ name }}Private::{{ name }}Private()
{
    
}

{{ name }}Private::~{{ name }}Private()
{
    
}

{% endif dpointer %}

{{ name }}::{{ name }}(QObject* parent = 0) : QObject(parent)
{
    
}

virtual ~{{ name }}()
{
    
}

{% for p in properties %}
{{ p.type|return_arg }} {{ name }}::{{ p|getter_name }}()
{
    Q_D(const {{ name }});
    return d->{{ name }};
}

void {{ name }}::{{ p|setter_name }}({{ p.type|pass_arg }} {{name}})
{
    Q_D({{ name }});
    d->{{ name }} = {{ name }};
}
{% endfor %}
