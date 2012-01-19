{% load grantlee_cppfilters %}

{{ license }}

{% if nameSpace %}
#ifndef {{ nameSpace|upper }}_{{ name|upper }}_H
#define {{ nameSpace|upper }}_{{ name|upper }}_H
{% else %}
#ifndef {{ name|upper }}_H
#define {{ name|upper }}_H
{% endif %}

// Includes from superclasses

{% if nameSpace %}
namespace {{ nameSpace }} {% templatetag openbrace %}
{% endif %}

class {{ name }}Private;

class {{ name }} {% if class.superclasses %}:{% endif %} {% for super in class.superclasses %} super{% if not forloop.last %}, {% endif %}{% endfor %}
{% templatetag openbrace %}
    Q_OBJECT
    {% for p in class.properties %}
    Q_PROPERTY({{ p.type }} {{ p.name }} {% if p.getter %}READ {{ p.getter }} {% endif %}{% if p.setter %}WRITE {{ p.setter }} {% endif %})
    {% endfor %}
    
public:
    {{ name }}(QObject* parent = 0);
    virtual ~{{ name }}();
    
    {% for p in class.properties %}
    {{ p|property_decl }}
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