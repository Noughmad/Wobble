{% load grantlee_cppfilters %}
/*
    {{ license }}
 */

{% if nameSpace %}
#ifndef {{ nameSpace|upper }}_{{ name|upper }}_P_H
#define {{ nameSpace|upper }}_{{ name|upper }}_P_H
{% else %}
#ifndef {{ name|upper }}_P_H
#define {{ name|upper }}_P_H
{% endif %}

// TODO: Includes from superclasses

{% if nameSpace %}
namespace {{ nameSpace }} {% templatetag openbrace %}
{% endif %}

class {{ name }};

class {{ name }}Private {% if class.superclasses %}:{% endif %} {% for super in class.superclasses %} {{ super }}Private{% if not forloop.last %}, {% endif %}{% endfor %}
{% templatetag openbrace %}
    
public:
    {{ name }}Private();
    virtual ~{{ name }}Private();
    
    {% for p in properties %}
    {{ p.type|return_arg }} {{ p.name }};
    {% endfor %}

{% templatetag closebrace %};
{% if nameSpace %}
{% templatetag closebrace %}
{% endif %}

#endif