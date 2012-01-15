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

#include <grantlee/engine.h>

#include <QtCore/QDir>

using namespace Grantlee;
using namespace Wobble;

const char* TemplateDir = "/home/miha/Build/share/templates/cpp/";

bool CppOutput::write(Wobble::Project* project, QVariantMap options)
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
    
    Engine* engine = new Engine();
    FileSystemTemplateLoader::Ptr loader = FileSystemTemplateLoader::Ptr( new FileSystemTemplateLoader() );
    loader->setTemplateDirs( QStringList() << TemplateDir );
    engine->addTemplateLoader( loader );
    
    // First, create the top-level CMakeLists.txt file
    Context* c = new Context();
    c->insert("project", project);
    c->insert("name", QVariant(project->name()));
        
    Template topLevelCmlTemplate = engine->loadByName("CMakeLists.txt");
    QFile topLevelCml(outDir + "CMakeLists.txt");
    topLevelCml.open(QIODevice::WriteOnly);
    topLevelCml.write(topLevelCmlTemplate->render(c).toLatin1());
    topLevelCml.close();
    
    if (project->projectType() == Project::Application)
    {
        Template mainTemplate = engine->loadByName("main.cpp");
        QFile mainFile(outDir + "main.cpp");
        mainFile.open(QIODevice::WriteOnly);
        mainFile.write(mainTemplate->render(c).toLatin1());
        mainFile.close();
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
