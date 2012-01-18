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

#include "identifier_p.h"
#include "identifier.h"

#include <QDebug>

using namespace Wobble;

IdentifierPrivate::IdentifierPrivate(const QString& name) : name(name)
{
    
}

IdentifierPrivate::~IdentifierPrivate()
{

}

Identifier::Identifier(const QString& name, Identifier* parent): QObject(parent), d_ptr(new IdentifierPrivate(name))
{
    setObjectName(name);
}

Identifier::Identifier(IdentifierPrivate& dd, QObject* parent): QObject(parent), d_ptr(&dd)
{
    Q_D(Identifier);
    setObjectName(d->name);
}

Identifier::~Identifier()
{
    delete d_ptr;
}

QString Identifier::name() const
{
    return objectName();
}

void Identifier::setName(const QString& name)
{
    Q_D(Identifier);
    d->name = name;
    setObjectName(name);
}

Identifier* Identifier::space() const
{
    return qobject_cast<Identifier*>(parent());
}

void Identifier::setSpace(Identifier* space)
{
    setParent(space);
}


QString Identifier::documentation() const
{
    Q_D(const Identifier);
    return d->documentation;
}

void Identifier::setDocumentation(const QString& documentation)
{
    Q_D(Identifier);
    d->documentation = documentation;
}

Identifier::AccessType Identifier::accessType() const
{
    Q_D(const Identifier);
    return (AccessType)d->accessType;
}

void Identifier::setAccessType(Identifier::AccessType accessType)
{
    Q_D(Identifier);
    d->accessType = accessType;
}

QString Identifier::fullName(const QString& separator) const
{
    Q_D(const Identifier);
    if (space())
    {
        return space()->fullName(separator) + separator + d->name;
    }
    else
    {
        return d->name;
    }
}

IdentifierList Identifier::members() const
{
    return findChildren<Identifier*>();
}

QDebug& operator<<(QDebug& stream, Wobble::Identifier* id) {
    stream << id->metaObject()->className() << " " << id->fullName("/");
    return stream.maybeSpace();
}

#include "identifier.moc"