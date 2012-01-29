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

#include "class.h"
#include "class_p.h"

#include "variable.h"
#include "function.h"

#include <QDebug>

using namespace Wobble;

ClassPrivate::ClassPrivate(const QString& name) : TypePrivate(name)
{
    features = Class::Persistent;
}

ClassPrivate::~ClassPrivate()
{
    
}

Class::Class(const QString& name, Identifier* parent): Type(*new ClassPrivate(name), parent)
{

}

Class::Class(ClassPrivate& dd, QObject* parent): Type(dd, parent)
{

}

Class::~Class()
{

}

Class::ClassList Class::superclasses()
{
    Q_D(const Class);
    return d->superclasses;
}

void Class::setSuperclasses(const ClassList& superclasses)
{
    Q_D(Class);
    d->superclasses = superclasses;
}

Class::Features Class::features() const
{
    Q_D(const Class);
    return (Features)d->features;
}

void Class::setFeatures(Class::Features features)
{
    Q_D(Class);
    d->features = features;
}

Class* Class::find(const QString& name)
{
    return 0;
}

VariableList Class::properties() const
{
    return findMembers<Variable*>();
}

FunctionList Class::methods() const
{
    return findMembers<Function*>();
}

#include "class.moc"
