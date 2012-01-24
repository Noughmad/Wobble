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

#include "djangofilters.h"

#include "src/core/query.h"
#include "src/core/variable.h"
#include "src/core/type.h"

using namespace Wobble;

QVariant QuerySetFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Query* query = input.value<Query*>();
    Q_CHECK_PTR(query);
    
    QString queryString = query->type()->name();
    
    return queryString;
}

QVariant FieldDeclarationFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Variable* var = input.value<Variable*>();
    Q_CHECK_PTR(var);
    
    // TODO: Map from Wobble type to Django field namespace
    // TODO: Consider other parameters to model fields, such as default value
    return var->type()->name();
}

Q_EXPORT_PLUGIN2(WobbleDjangoFilters, DjangoFilters)

