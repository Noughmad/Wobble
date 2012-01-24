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

#ifndef DJANGOFILTERS_H
#define DJANGOFILTERS_H

#include <grantlee/taglibraryinterface.h>
#include <grantlee/filter.h>

#include <QtPlugin>

class FieldDeclarationFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class QuerySetFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class DjangoFilters : public QObject, Grantlee::TagLibraryInterface
{
    Q_OBJECT
    Q_INTERFACES(Grantlee::TagLibraryInterface)
    
    virtual QHash< QString, Grantlee::Filter* > filters(const QString& name = QString())
    {
        QHash<QString, Grantlee::Filter*> f;
        f["field_declaration"] = new FieldDeclarationFilter();
        f["queryset"] = new QuerySetFilter();
        return f;
    }
};

#endif // DJANGOFILTERS_H
