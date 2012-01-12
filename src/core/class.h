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

#ifndef WOBBLE_CLASS_H
#define WOBBLE_CLASS_H

#include "identifier.h"

namespace Wobble {
    
    class Variable;
    class Function;
    class Connection;
    
    class ClassPrivate;

class Class : public Identifier
{
    Q_OBJECT
    
    Q_ENUMS(Feature)
    Q_FLAGS(Features)
    
    Q_PROPERTY(QList<Variable> members READ members WRITE setMembers)
    Q_PROPERTY(QList<Function> methods READ methods WRITE setMethods)
    Q_PROPERTY(QList<Class> superclasses READ superclasses WRITE setSuperclasses)
    Q_PROPERTY(Features features READ features WRITE setFeatures)
    
    
public:
    enum Feature
    {
        NoFeatures = 0,
        Persistent = 0x01,
        Serializable = 0x02,
        Abstract = 0x04
    };
    
    Q_DECLARE_FLAGS(Features, Feature)
    
    explicit Class(QObject* parent = 0);
    virtual ~Class();
    
private:
    Q_DECLARE_PRIVATE(Class)
};

}

#endif // WOBBLE_CLASS_H
