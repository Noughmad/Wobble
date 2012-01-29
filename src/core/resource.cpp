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

#include "resource.h"
#include "resource_p.h"

using namespace Wobble;

ResourcePrivate::ResourcePrivate(const QString& name) : IdentifierPrivate(name)
{
}

Wobble::ResourcePrivate::~ResourcePrivate()
{

}

Resource::Resource(const QString& name, Wobble::Identifier* parent): Identifier(*new ResourcePrivate(name), parent)
{
    
}

Resource::Resource(Wobble::ResourcePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Resource::~Resource()
{

}

QString Resource::filename() const
{
    Q_D(const Resource);
    return d->filename;
}

void Resource::setFilename(const QString filename)
{
    Q_D(Resource);
    d->filename = filename;
}

#include "resource.moc"
