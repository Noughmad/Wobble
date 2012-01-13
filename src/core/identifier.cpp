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

using namespace Wobble;

IdentifierPrivate::IdentifierPrivate()
{

}

IdentifierPrivate::~IdentifierPrivate()
{

}

Identifier::Identifier(const QString& name, Identifier* space, QObject* parent): QObject(parent), d_ptr(new IdentifierPrivate)
{
    Q_D(Identifier);
    d->name = name;
    d->space = space;
}

Identifier::Identifier(IdentifierPrivate& dd, QObject* parent): QObject(parent), d_ptr(&dd)
{

}

Identifier::~Identifier()
{
    delete d_ptr;
}

QString Identifier::name() const
{
    Q_D(const Identifier);
    return d->name;
}

void Identifier::setName(const QString& name)
{
    Q_D(Identifier);
    d->name = name;
}

Identifier* Identifier::space() const
{
    Q_D(const Identifier);
    return d->space;
}

void Identifier::setSpace(Identifier* space)
{
    Q_D(Identifier);
    d->space = space;
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


QString Identifier::fullName(const QString& separator) const
{
    Q_D(const Identifier);
    if (d->space)
    {
        return d->space->fullName(separator) + separator + d->name;
    }
    else
    {
        return d->name;
    }
}







