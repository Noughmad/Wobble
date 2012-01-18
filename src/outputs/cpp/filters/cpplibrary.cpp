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

#include "cpplibrary.h"

#include "src/core/variable.h"
#include "src/core/type.h"

#include <QDebug>

using namespace Wobble;

QVariant PropertyDeclarationFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    VariablePtr property = input.value<VariablePtr>();
    if (!property->type())
    {
        qDebug() << "Every property needs a type in C++";
        return QVariant();
    }
    
    QString type = property->type()->name();
    
    return QVariant();
}

QVariant PropertyDefinitionFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    return QVariant();
}

Q_EXPORT_PLUGIN2(WobbleCppFilters, CppLibrary)

