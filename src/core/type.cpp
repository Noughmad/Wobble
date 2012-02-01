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

#include "type.h"
#include "type_p.h"

using namespace Wobble;

typedef QMap<Type::StandardType, Type*> TypeMap;

Q_GLOBAL_STATIC(TypeMap, stdTypes)

TypePrivate::TypePrivate(const QString& name) : IdentifierPrivate(name)
{
    valueType = 0;
    keyType = 0;
    standardType = Type::Custom;
}

Wobble::TypePrivate::~TypePrivate()
{

}

Type::Type(const QString& name, Wobble::Identifier* parent): Identifier(*new TypePrivate(name), parent)
{
    
}

Type::Type(Wobble::TypePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Type::~Type()
{

}

Type::Source Type::source() const
{
    Q_D(const Type);
    return (Source)d->source;
}

void Type::setSource(Type::Source source)
{
    Q_D(Type);
    d->source = source;
}

bool Type::isPod() const
{
    Q_D(const Type);
    return d->pod;
}

void Type::setPod(bool pod)
{
    Q_D(Type);
    d->pod = pod;
}

bool Type::isObject() const
{
    Q_D(const Type);
    return d->object;
}

void Type::setObject(bool object)
{
    Q_D(Type);
    d->object = object;
}

void Type::setKeyType(Type* keyType)
{
    Q_D(Type);
    d->keyType = keyType;
}

Type* Type::keyType() const
{
    Q_D(const Type);
    return d->keyType;
}

void Type::setValueType(Type* valueType)
{
    Q_D(Type);
    d->valueType = valueType;
}

Type* Type::valueType() const
{
    Q_D(const Type);
    return d->valueType;
}


Type* Type::findByName(const QString& name)
{
    Type* t = new Type(name);
    t->setObject(false);
    t->setPod(name != "string");
    return t;
}

Type* Type::fromStandardType(Type::StandardType type)
{
    if (!stdTypes()->contains(type))
    {
        Type* t = new Type(standardTypeName(type));
        t->setStandardType(type);
        stdTypes()->insert(type, t);
    }
    return stdTypes()->value(type);
}

QString Type::standardTypeName(Type::StandardType type)
{
    switch (type)
    {
        case Boolean:
            return "bool";
            
        case Integer:
            return "int";
            
        case Character:
            return "char";
            
        case Float:
            return "float";
            
        case String:
            return "string";
            
        case File:
            return "file";
            
        case DateTime:
            return "time";
            
        default:
            qWarning() << "standardTypeName called with a non-standard type" << type;
            return QString();
    }
}

Type::StandardType Type::standardType() const
{
    Q_D(const Type);
    return (StandardType)d->standardType;
}

void Type::setStandardType(Type::StandardType type)
{
    Q_D(Type);
    d->standardType = (int)type;
}

Type* Type::list(Type* values)
{
    Type* t = new Type("list-of-" + values->name(), values->topLevel());
    t->setStandardType(Type::List);
    t->setValueType(values);
    return t;
}

Type* Type::map(Type* keys, Type* values)
{
    Type* t = new Type(QString("map-of-%1-%2").arg(keys->name()).arg(values->name()), keys->topLevel());
    t->setStandardType(Type::Map);
    t->setKeyType(keys);
    t->setValueType(values);
    return t;
}



#include "type.moc"
