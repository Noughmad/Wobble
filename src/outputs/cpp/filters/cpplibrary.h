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

#ifndef CPPLIBRARY_H
#define CPPLIBRARY_H

#include <grantlee/taglibraryinterface.h>
#include <grantlee/filter.h>

#include <QtPlugin>
#include <QtDebug>

class IncludeLineFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class PropertyDeclarationFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class PropertyDefinitionFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class ReturnArgFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument, bool autoescape) const;
};

class PassArgFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class GetterNameFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class SetterNameFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class CppLibrary : public QObject, public Grantlee::TagLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(Grantlee::TagLibraryInterface)
    
public:
    CppLibrary(QObject* parent = 0) 
    : QObject(parent)
    {
        
    };
    virtual ~CppLibrary() {}

    virtual QHash< QString, Grantlee::Filter* > filters(const QString& name = QString())
    {
        QHash<QString, Grantlee::Filter*> filters;

        filters["property_declaration"] = new PropertyDeclarationFilter();
        filters["property_definition"] = new PropertyDefinitionFilter();
        filters["setter_name"] = new SetterNameFilter();
        filters["getter_name"] = new GetterNameFilter();
        filters["return_arg"] = new ReturnArgFilter();
        filters["pass_arg"] = new PassArgFilter();
        filters["include_line"] = new IncludeLineFilter();
        
        return filters;
    }
};

#endif // CPPLIBRARY_H
