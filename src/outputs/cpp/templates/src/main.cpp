{{ license }}

#include <{{ appClass }}>
#include <QString>

{% for i in localIncludes %}
#include "{{ i }}"
{% endfor %}


using namespace Wobble;

int main(int argc, char** argv)
{
    {{ appClass }} app(argc, argv);
    
    app.setApplicationName(QLatin1String("{{ name }}"));
    app.setApplicationName(QLatin1String("{{ version }}"));
    
    /*
     * TODO: Define application name, version
     */
    
    {% if mainClass %}
    {{ mainClass }}* m = new {{ mainClass }};
    {% else %}
    /*
     * TODO: Initialize the program here
     */
    {% endif %}
    
    return app.exec();
}
