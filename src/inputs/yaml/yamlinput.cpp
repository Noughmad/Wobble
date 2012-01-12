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

#include "yamlinput.h"
#include <src/core/project.h>
#include <fstream>

#include "yaml-cpp/parser.h"
#include "yaml-cpp/node.h"

bool YamlInput::read(Wobble::Project* project, QVariantMap options)
{
    std::ifstream stream(options["filename"].toByteArray());
    YAML::Parser parser(stream);
    
    YAML::Node node;
    if (!parser.GetNextDocument(node))
    {
        return false;
    }
    
    QString name = QString::fromStdString(node["name"].to<std::string>());
}

QString YamlInput::name()
{
    return "YAML";
}

YamlInput::YamlInput(QObject* parent): Input(parent)
{

}

YamlInput::~YamlInput()
{

}

