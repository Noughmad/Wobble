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

using namespace Wobble;

int main(int argc, char** argv)
{
    QCoreApplication app(argc, argv);
    
    QPluginLoader loader("/home/miha/Programiranje/Wobble/build/src/inputs/yaml/libWobbleYamlInput.so");
    Input* input = qobject_cast<Input*>(loader.instance());
    if (!input)
    {
        qDebug() << "Unable to load input plugin";
        qDebug() << loader.errorString();
        return 0;
    }
    
    Project* project = new Project();
    input->read(project, QVariantMap());
    
    QPluginLoader oloader("/home/miha/Programiranje/Wobble/build/src/outputs/debug/libWobbleDebugOutput.so");
    Output* output = qobject_cast< Output* >(oloader.instance());
    
    if (!output)
    {
        qDebug() << "Unable to load output plugin";
        qDebug() << oloader.errorString();
        return 0;
    }
    
    output->write(project, QVariantMap());
    
    return 0;
}