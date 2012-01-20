{% load grantlee_cppfilters %}

{{ license }}

{% if nameSpace %}
#ifndef {{ nameSpace|upper }}_{{ name|upper }}_H
#define {{ nameSpace|upper }}_{{ name|upper }}_H
{% else %}
#ifndef {{ name|upper }}_H
#define {{ name|upper }}_H
{% endif %}

// TODO: Includes from superclasses

{% if nameSpace %}
namespace {{ nameSpace }} {% templatetag openbrace %}
{% endif %}

class {{ name }}Private;

class {{ name }} {% if class.superclasses %}:{% endif %} {% for super in class.superclasses %} super{% if not forloop.last %}, {% endif %}{% endfor %}
{% templatetag openbrace %}
    Q_OBJECT
    {% for p in properties %}
    Q_PROPERTY({{ p.type.name }} {{ p.name }} READ {{ p|getter_name }} {% if not p.isConstant %} WRITE {{ p|setter_name }} {% endif %})
    {% endfor %}
    
public:
    {{ name }}(QObject* parent = 0);
    virtual ~{{ name }}();
    
    {% for p in properties %}
    {{ p.type|return_arg }} {{ p|getter_name }}();
    void {{ p|setter_name }}({{ p.type|pass_arg }} {{ p.name }});
    {% endfor %}
    
protected:
{% if not class.superclasses %}
    {{ name }}Private* const d_ptr;
{% endif %}
    {{ name }} ({{ name }}Private& dd, QObject* parent = 0);

private:
    Q_DECLARE_PRIVATE({{ name }})
{% templatetag closebrace %};
{% if nameSpace %}
{% templatetag closebrace %}
{% endif %}

#endif