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
namespace {{ nameSpace }} {
{% endif %}

class {{ name }}Private;

class {{ name }} {% if class.superclasses %}:{% endif %} {% for super in class.superclasses %} super{% if not forloop.last %}, {% endif %}{% endfor %}
{
    Q_OBJECT
    {% for p in class.properties %}
    Q_PROPERTY({{ p.type }} {{ p.name }} {% if p.getter %}READ {{ p.getter }} {% endif %}{% if p.setter %}WRITE {{ p.setter }} {% endif %})
    {% endfor %}
    
public:
    {{ name }}(QObject* parent = 0);
    virtual ~{{ name }}();
    
    {% for p in class.properties %}
    {{ p|getter }}
    {{ p|setter }}
    {% endfor %}
    
protected:
{% if not class.superclasses %}
    {{ name }}Private* const d_ptr;
{% endif %}
    {{ name }} ({{ name }}Private& dd, QObject* parent = 0);

private:
    Q_DECLARE_PRIVATE({{ class.name }})
};
{% if nameSpace %}
}
{% endif %}

#endif