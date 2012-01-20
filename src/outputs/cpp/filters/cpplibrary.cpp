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

QString functionCase(const QString str)
{
    return str[0].toUpper() + str.mid(1);
}

QString getterName(Variable* var)
{
    QString name = var->name();
    if (var->type()->name() == "bool")
    {
        name = "is" + functionCase(name);
    }
    return name;
}

QString setterName(Variable* var)
{
    return "set" + functionCase(var->name());
}

QVariant GetterNameFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Variable* property = input.value<Variable*>();
    return getterName(property);
}

QVariant SetterNameFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Variable* property = input.value<Variable*>();
    return setterName(property);
}


QVariant PropertyDeclarationFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    Variable* property = input.value<Variable*>();
    Type* type = property->type();
    
    if (!type)
    {
        qDebug() << "Every property needs a type in C++";
        return QVariant();
    }
    
    QString name = property->name();
    QString setterArg, getterValue;
    qDebug() << type->name() << type->isObject() << type->isPod();
    if (type->isObject())
    {
        getterValue = type->name() + '*';
        setterArg = getterValue;
    }
    else 
    {
        getterValue = type->name();
        if (!type->isPod())
        {
            setterArg = "const " + getterValue + '&';
        }
        else
        {
            setterArg = getterValue;
        }
    }
    
    const QString getter = QString("%1 %2() const;").arg(getterValue).arg(getterName(property));
    const QString setter = QString("void %1(%2 %3);").arg(setterName(property)).arg(setterArg).arg(name);
        
    return QVariant(getter + '\n' + setter + '\n');
}

QVariant PropertyDefinitionFilter::doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const
{
    return QVariant();
}

Q_EXPORT_PLUGIN2(WobbleCppFilters, CppLibrary)

