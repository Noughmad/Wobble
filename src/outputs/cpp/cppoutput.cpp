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

#include "cppoutput.h"

#include "src/core/project.h"
#include "src/core/class.h"
#include "src/core/variable.h"
#include "src/utils/templates.h"

#include <grantlee/engine.h>

#include <QtCore/QDir>

using namespace Grantlee;
using namespace Wobble;

const char* TemplateDir = "/home/miha/Build/share/templates/cpp/";

bool CppOutput::write(const Project* project, QVariantMap options)
{
    QString outDir = options["outputDirectory"].toString();
    if (outDir.isEmpty())
    {
        return false;
    }
    
    QDir dir(outDir);
    if (!dir.exists())
    {
        dir.mkpath(outDir);
    }
    
    Templates::engine()->loadByName("grantlee_cppfilters");
    
    // First, create the top-level CMakeLists.txt file
    Context* c = new Context();
    c->insert("project", project);
    c->insert("name", QVariant(project->name()));
        
    Template topLevelCmlTemplate = Templates::getTemplate("CMakeLists.top");
    QFile topLevelCml(outDir + "CMakeLists.txt");
    topLevelCml.open(QIODevice::WriteOnly);
    topLevelCml.write(topLevelCmlTemplate->render(c).toLatin1());
    topLevelCml.close();
    
    if (project->projectType() == Project::Application)
    {
        Template mainTemplate = Templates::getTemplate("main.cpp");
        QFile mainFile(outDir + "main.cpp");
        mainFile.open(QIODevice::WriteOnly);
        mainFile.write(mainTemplate->render(c).toLatin1());
        mainFile.close();
    }
    
    Template classTemplate = Templates::getTemplate("class.h");
    dir.mkpath(outDir + "src");
    
    qDebug() << classTemplate->errorString();
    
    foreach (Class* c, project->findChildren<Class*>())
    {
        QFile file(outDir + "src/" + c->name().toLower() + ".h");
        if (!file.open(QIODevice::WriteOnly))
        {
            qDebug() << "Couln't open class file";
            continue;
        }
        
        Context* context = new Context();
        context->insert("name", c->name());
        context->insert("license", "This is License");
        context->insert("nameSpace", project->name());
        context->insert("properties", QVariant::fromValue<QList<Wobble::Variable*> >(c->findChildren<Wobble::Variable*>()));
        
        file.write(classTemplate->render(context).toLatin1());
        file.close();
    }
}

QString CppOutput::name()
{
    return "C++";
}

CppOutput::CppOutput(QObject* parent): Output(parent)
{

}

CppOutput::~CppOutput()
{

}

Q_EXPORT_PLUGIN2(WobbleCppOutput, CppOutput)

#include "cppoutput.moc"
