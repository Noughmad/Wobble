{{ license }}

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
    {{ class.name }}(QObject* parent = 0);
    
protected:
    Q_DECLARE_PRIVATE({{ class.name }})
};
{% if nameSpace %}
}
{% endif %}

