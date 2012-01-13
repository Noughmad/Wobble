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
#include "src/core/project.h"
#include "src/core/class.h"
#include <fstream>

#include "yaml-cpp/parser.h"
#include "yaml-cpp/node.h"

using namespace Wobble;
using namespace YAML;
using namespace std;

YamlInput::YamlInput(QObject* parent): Input(parent)
{
   
}

YamlInput::~YamlInput()
{

}

QString YamlInput::name()
{
    return "YAML";
}

bool YamlInput::read(Wobble::Project* project, QVariantMap options)
{
    mProject = project;
    ifstream stream("/home/miha/Programiranje/Wobble/test/zoo.yaml");
    YAML::Parser parser(stream);
    
    YAML::Node node;
    if (!parser.GetNextDocument(node))
    {
        return false;
    }
    
    for(YAML::Iterator it=node.begin();it!=node.end();++it) {
        string key;
        it.first() >> key;
        
        if (key == "project")
        {
            project->setName(readString(it.second()));
        }
        else if (key == "classes")
        {
            readClasses(it.second());
        }
    }
}

QString YamlInput::readString(const YAML::Node& node)
{
    string string;
    node >> string;
    return QString::fromStdString(string);
}

void YamlInput::readClasses(const YAML::Node& node)
{
    Class* c;
    for(YAML::Iterator it=node.begin();it!=node.end();++it) {
        c = new Class(readString((*it)["name"]), mProject);
        if (const Node* super = it->FindValue("super"))
        {
            QList<Class*> superClasses;
            if (super->Type() == NodeType::Scalar)
            {
                superClasses << mProject->findMember<Class>(readString(*super));
            }
            else if (super->Type() == NodeType::Sequence)
            {
                for (Iterator si = super->begin(); si != super->end(); ++si)
                {
                    superClasses << mProject->findMember<Class>(readString(*si));
                }
            }
            c->setSuperclasses(superClasses);
        }
    }
}

Q_EXPORT_PLUGIN2(WobbleYamlInput, YamlInput)

#include "yamlinput.moc"
