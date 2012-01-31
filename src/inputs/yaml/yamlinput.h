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

#ifndef YAMLINPUT_H
#define YAMLINPUT_H

#include "src/core/input.h"
#include "src/utils/defaultparser.h"

#include <QtPlugin>

namespace YAML
{
    class Node;
}

namespace Wobble
{
    class Identifier;
}

class YamlInput : public Wobble::Input
{
    Q_OBJECT
    Q_INTERFACES(Wobble::Input)
public:
    explicit YamlInput(QObject* parent = 0);
    virtual ~YamlInput();

    virtual bool read(Wobble::Project* project, QVariantMap options);
    virtual QString name();
    
    QString readString(const YAML::Node& node);
    QString readString(const YAML::Node* node);
    
private:
    void readClass(const YAML::Node& node);
    void readQuery(const YAML::Node& node);
    void readView(const YAML::Node& node);
    void readVariables(const YAML::Node& node, Wobble::Identifier* parent);
    Wobble::Project* mProject;
    Wobble::DefaultParser mParser;
};

#endif // YAMLINPUT_H
