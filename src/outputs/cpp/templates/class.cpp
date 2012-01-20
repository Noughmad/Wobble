{% load grantlee_cppfilters %}
{{ license }}

#include "{{ name|lower }}.h"
#include "{{ name|lower }}_p.h"

{% if nameSpace %}using namespace nameSpace;{% endif %}

{{ name }}Private::{{ name }}Private()
{
    
}

{{ name }}Private::~{{ name }}Private()
{
    
}

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
