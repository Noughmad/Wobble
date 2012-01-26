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

#include <QCoreApplication>
#include <QPluginLoader>
#include <QDebug>

#include "src/core/input.h"
#include "src/core/project.h"
#include "src/core/output.h"
#include <QDir>

#include "src/core/config.h"

using namespace Wobble;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    
    QPluginLoader loader(QString(PluginDir) + "/libWobbleYamlInput.so");
    Input* input = qobject_cast<Input*>(loader.instance());
    if (!input)
    {
        qDebug() << "Unable to load input plugin";
        qDebug() << loader.errorString();
        return 0;
    }
    
    Project* project = new Project();
    project->setProjectType(Project::Application);
    input->read(project, QVariantMap());
    
    QVariantMap options;
    options["outputDirectory"] = "/home/miha/Build/test/";
    foreach (const QFileInfo& plugin, QDir(PluginDir).entryInfoList(QDir::Files))
    {
        QPluginLoader l(plugin.absoluteFilePath());
        Output* output = qobject_cast< Output* >(l.instance());
        
        if (output)
        {
            qDebug() << "Loaded output " << plugin.absoluteFilePath();
            output->write(project, options);
        }
    }
    
    return 0;
}