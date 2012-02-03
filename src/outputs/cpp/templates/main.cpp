{% load grantlee_cppfilters %}
{{ license }}

#include <QString>

{{ appClass|include_line }}

{{ project.mainWindow|include_line }}

using namespace Wobble;

int main(int argc, char** argv)
{
    {{ appClass }} app(argc, argv);
    
    app.setApplicationName(QLatin1String("{{ project.name }}"));
    app.setApplicationVersion(QLatin1String("{{ project.version }}"));
    
    /*
     * TODO: Define application name, version
     */
    
    {% if project.mainWindow %}
    {{ project.mainWindow.name }}* m = new {{ project.mainWindow.name }};
    m->show();
    {% else %}
    /*
     * TODO: Initialize the program here
     */
    {% endif %}
    
    return app.exec();
}
