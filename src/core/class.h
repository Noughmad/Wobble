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

#include "type.h"

namespace Wobble {
    
    W_FORWARD(Variable)
    W_FORWARD(Function)
    W_FORWARD(Connection)
    
    class ClassPrivate;

    /**
     * @brief Representation of class
     * 
     * This represents a custom object type (usually called "class"). 
     * It supports inheritance, so each class can have any number of superclasses. 
     **/
    class WOBBLE_EXPORT Class : public Type
{
    Q_OBJECT
    
    Q_ENUMS(Feature)
    Q_FLAGS(Features)
    
    Q_PROPERTY(ClassList superclasses READ superclasses WRITE setSuperclasses)
    Q_PROPERTY(Features features READ features WRITE setFeatures)
    Q_PROPERTY(VariableList properties READ properties)

    /*
    Q_PROPERTY(QList<Variable*> members READ members STORED false)
    Q_PROPERTY(QList<Function*> methods READ methods STORED false)
    */
    
    W_DECLARE_POINTER(Class)
    
public:
    enum Feature
    {
        NoFeatures = 0,
        Persistent = 0x01,
        Serializable = 0x02,
        Abstract = 0x04,
        Shared = 0x08
    };
    
    Q_DECLARE_FLAGS(Features, Feature)
    
    Class(const QString& name, Wobble::Identifier* parent = 0);
    virtual ~Class();
    
    static Class* find(const QString& name);
    
    ClassList superclasses();
    void setSuperclasses(const ClassList& superclasses);
    
    Features features() const;
    void setFeatures(Features features);
    
    VariableList properties() const;
    
    W_DECLARE_PRIVATE(Class)
};

W_DECLARE_POINTER(Class)

}

W_DECLARE_METATYPE(Class)

#endif // WOBBLE_CLASS_H
