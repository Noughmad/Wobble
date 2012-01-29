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
#include "src/core/variable.h"
#include "src/core/query.h"
#include <fstream>

#include "yaml-cpp/parser.h"
#include "yaml-cpp/node.h"
#include <QStringList>
#include "src/core/view.h"
#include "src/core/function.h"

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
    
    qDebug() << "Reading node of size " << node.size();
    
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
        else if (key == "queries")
        {
            for(YAML::Iterator qi = it.second().begin(); qi != it.second().end(); ++qi)
            {
                readQuery(*qi);
            }
        }
        else if (key == "views")
        {
            for(YAML::Iterator vi = it.second().begin(); vi != it.second().end(); ++vi)
            {
                readView(*vi);
            }
        }
        else if (key == "license")
        {
            project->setLicense(readString(it.second()));
        }
    }
    
    return true;
}

QString YamlInput::readString(const YAML::Node& node)
{
    string str;
    node >> str;
    return QString::fromStdString(str);
}

QString YamlInput::readString(const Node* node)
{
    if (!node)
    {
        return QString();
    }
    return readString(*node);
}

void YamlInput::readQuery(const Node& node)
{
    QString name = readString(node["name"]);
    Class* type = mProject->findChild<Class*>(readString(node["type"]));
    if (!type)
    {
        qWarning() << "Query type is not a class type";
        return;
    }
    
    qDebug() << "Adding query" << name;
    Query* query = new Query(name, type, mProject);
    
    if (const YAML::Node* queryType = node.FindValue("result"))
    {
        // TODO: Map from string to appropriate values
        query->setQueryType(Query::GetMany);
    }
    else
    {
        query->setQueryType(Query::GetMany);
    }
    
    if (const YAML::Node* filters = node.FindValue("filters"))
    {
        for (YAML::Iterator it = filters->begin(); it != filters->end(); ++it)
        {
            QStringList list = readString(*it).split(" ");
            if (list.size() != 3)
            {
                qWarning() << "Bad filter line" << list;
                continue;
            }
            Variable* var = type->findChild<Variable*>(list.first());
            if (!var)
            {
                qWarning() << "Type" << type->name() << "has no property named" << list.first();
                continue;
            }
            
            Query::Filter f;
            f.var = var;
            f.value = list.last();
            
            // TODO: Map from operation symbols to Query::FilterType enum
            f.operation = Query::Equals;
            
            query->addFilter(f);
        }
    }
}

void YamlInput::readClasses(const YAML::Node& node)
{
    Class* c;
    for(YAML::Iterator it=node.begin();it!=node.end();++it) {
        const QString name = readString((*it)["name"]);
        qDebug() << "Reading class " << name;
        c = new Class(name, mProject);
        if (const Node* super = it->FindValue("super"))
        {
            ClassList superClasses;
            if (super->Type() == NodeType::Scalar)
            {
                superClasses << mProject->findChild<Class*>(readString(*super));
            }
            else if (super->Type() == NodeType::Sequence)
            {
                for (Iterator si = super->begin(); si != super->end(); ++si)
                {
                    superClasses << mProject->findChild<Class*>(readString(*si));
                }
            }
            c->setSuperclasses(superClasses);
        }
        qDebug() << "Superclasses done, now reading properties";
        if (const Node* properties = it->FindValue("properties"))
        {
            for (Iterator pi = properties->begin(); pi != properties->end(); ++pi)
            {
                QString name = readString(pi->FindValue("name"));
                QString type = readString(pi->FindValue("type"));
                QString value = readString(pi->FindValue("value"));
                Type* parsedType = mParser.parseType(type, mProject);
                Variable* property = new Variable(name, parsedType, c);
                if (!value.isEmpty())
                {
                    property->setDefaultValue(mParser.parseValue(value, parsedType, c));
                }
            }
        }
        if (const Node* methods= it->FindValue("functions"))
        {
            for (Iterator pi = methods->begin(); pi != methods->end(); ++pi)
            {
                QString name = readString(pi->FindValue("name"));
                QString type = readString(pi->FindValue("type"));
                Function* f = new Function(name, mParser.parseType(type, mProject), c);
                if (const Node* args = pi->FindValue("arguments"))
                {
                    for (Iterator arg = args->begin(); arg != args->end(); ++arg)
                    {
                        f->addArgument(readString(arg->FindValue("name")), mParser.parseType(readString(arg->FindValue("type")), mProject));
                    }
                }
            }
        }
    }
}

void YamlInput::readView(const YAML::Node& node)
{
    QString name = readString(node["name"]);
    View* v = new View(name, mProject);
    QString type = readString(node["type"]);
    if (type == "list")
    {
        v->setViewType(View::ListView);
        v->setListItem(mProject->findChild<View*>(readString(node["item"])));
    }
    else
    {
        // TODO: Expand the switch to other standard types
        v->setViewType(View::LineView);
    }
    if (const YAML::Node* queries = node.FindValue("queries"))
    {
        for (YAML::Iterator it = queries->begin(); it != queries->end(); ++it)
        {
            if ((*it).Type() == NodeType::Scalar)
            {
                qDebug() << "Adding existing query" << readString(*it) << "to view" << name;
                v->addQuery(mProject->findChild<Query*>(readString(*it)));
            }
            else
            {
                qDebug() << "Adding new query" << readString((*it)["name"]) << "to view" << name;
                readQuery(*it);
                v->addQuery(mProject->findChild<Query*>(readString((*it)["name"])));
            }
        }
    }
}

Q_EXPORT_PLUGIN2(WobbleYamlInput, YamlInput)

#include "yamlinput.moc"
