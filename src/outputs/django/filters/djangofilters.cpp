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
    
    QString queryString = query->type()->name() + ".objects";
    if (query->filters().isEmpty())
    {
        queryString += ".all()";
    }
    else
    {
        foreach(const Query::Filter& filter, query->filters())
        {
            queryString += ".filter(" + filter.var->name();
            if (filter.operation != Query::Equals)
            {
                // TODO: add marks like __gt or __iexact
            }
            queryString += " = " + filter.value;
        }
    }
    
    return queryString;
}

QVariant FieldDeclarationFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Variable* var = input.value<Variable*>();
    Q_CHECK_PTR(var);

    QString line;

    QString type = var->type()->name();
    if (type == Type::standardTypeName(Type::Integer))
    {
        line = "IntegerProperty(";
    }
    else if (type == Type::standardTypeName(Type::Boolean))
    {
        line = "BooleanProperty(";
    }
    else if (type == Type::standardTypeName(Type::Float))
    {
        line = "FloatProperty(";
    }
    else if (type == Type::standardTypeName(Type::String))
    {
        line = "TextProperty(";
    }
    else if (type == Type::standardTypeName(Type::DateTime))
    {
        line = "DateTimeProperty(";
    }
    // TODO: Check for other types
    else if (type == var->space()->name())
    {
        line = "ForeignKeyProperty('self', blank=True, null=True,";
    }
    else
    {
        line = "ForeignKeyProperty(" + type;
    }

    if (var->defaultValue().isValid())
    {
        line += "default=";
        line += var->formatValue();
        line += ", ";
    }

    if (line.endsWith(", "))
    {
        line.chop(2);
    }

    return Grantlee::SafeString(line + ')', Grantlee::SafeString::IsSafe);
}

Q_EXPORT_PLUGIN2(WobbleDjangoFilters, DjangoFilters)

