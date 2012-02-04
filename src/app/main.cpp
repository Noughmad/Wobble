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
#include <QDebug>

#include "src/core/input.h"
#include "src/core/project.h"
#include "src/core/output.h"

#include "src/core/plugins.h"

using namespace Wobble;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    
    Input* input = Plugins::loadInput("YAML");

    Project* project = new Project();
    project->setProjectType(Project::Application);
    QVariantMap inputOptions;
    inputOptions["filename"] = "/home/miha/Programiranje/Wobble/test/ntasks.yaml";
    input->read(project, inputOptions);
    
    QVariantMap options;
    options["outputDirectory"] = "/home/miha/Build/test/";
    options["pythonExecutable"] = "python2";
    foreach (const QByteArray& name, Plugins::availableOutputs())
    {
        Output* output = Plugins::loadOutput(name);
        
        if (output)
        {
            qDebug() << "Loaded output " << name;
            output->write(project, options);
        }
    }
    
    return 0;
}