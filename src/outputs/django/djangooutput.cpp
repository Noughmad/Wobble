/*
    This file is part of Wobble, a code generation framework
    Copyright (C) 2012  Miha Čančula miha@noughmad.eu

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include "djangooutput.h"

#include "src/core/project.h"
#include "src/core/class.h"
#include "src/core/view.h"

#include <grantlee/engine.h>

#include <QtCore/QDir>
#include <QProcess>

#include "src/utils/templates.h"

using namespace Grantlee;
using namespace Wobble;

const char* TemplateDir = "/home/miha/Build/share/templates/django/";

bool DjangoOutput::write(const Project* project, QVariantMap options)
{ 
    const QString outDir = options["outputDirectory"].toString();
    if (outDir.isEmpty())
    {
        return false;
    }
    
    QDir dir(outDir);
    if (!dir.exists())
    {
        dir.mkpath(outDir);
    }
    
    QProcess process;
    process.setWorkingDirectory(dir.absolutePath());
    QStringList args;
    
    if (project->projectType() == Project::Application)
    {
        args << "startproject";
        const QString projectFolder = project->name() + "site";
        args << projectFolder;
        process.start("django-admin", args);
        
        if (!process.waitForStarted())
        {
            process.start("django-admin.py", args);
        }
        
        if (!process.waitForStarted())
        {
            // TODO: Warn the user that he/she has to install Django
            return false;
        }
        
        if (!process.waitForFinished())
        {
            return false;
        }
        
        dir.cd(projectFolder);
        process.setWorkingDirectory(dir.absolutePath());
        args.clear();
    }
    
    args << "manage.py" << "startapp" << project->name().toLower();
    const QString pythonExe = options.value("pythonExecutable", QVariant("python")).toString();
    process.start(pythonExe, args);
    
    if (!process.waitForFinished())
    {
        return false;
    }
    
    Templates::engine()->loadLibrary("grantlee_djangofilters");
     
    Context* context = new Context();
    context->insert("project", project);
    context->insert("name", QVariant(project->name()));
    
    ClassList classes;
    foreach (Class* c, project->findChildren<Class*>())
    {
        if (c->features() & Class::Persistent)
        {
            classes << c;
        }
    }
    context->insert("classes", QVariant::fromValue<ClassList>(classes));
        
    Template modelsTemplate = Templates::getTemplate("models.py");
    QFile modelsFile(outDir + "models.py");
    modelsFile.open(QIODevice::WriteOnly);
    modelsFile.write(modelsTemplate->render(context).toLatin1());
    modelsFile.close();
    
    ViewList views = project->findChildren<View*>();
    context->insert("views", QVariant::fromValue(views));
    
    Template viewsTemplate = Templates::getTemplate("views.py");
    QFile viewsFile(outDir + "views.py");
    viewsFile.open(QIODevice::WriteOnly);
    viewsFile.write(viewsTemplate->render(context).toLatin1());
    viewsFile.close();
    
    return true;
}

QString DjangoOutput::name()
{
    return "Django";
}

DjangoOutput::DjangoOutput(QObject* parent): Output(parent)
{

}

DjangoOutput::~DjangoOutput()
{

}

Q_EXPORT_PLUGIN2(WobbleDjangoOutput, DjangoOutput)

#include "djangooutput.moc"
