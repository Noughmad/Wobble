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

class PropertyDeclarationFilter : public Grantlee::Filter
{
    virtual QVariant doFilter(const QVariant& input, const QVariant& argument = QVariant(), bool autoescape = false) const;
};

class PropertyDefinitionFilter : public Grantlee::Filter
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
        m_filters["property_decl"] = new PropertyDeclarationFilter();
        m_filters["property_def"] = new PropertyDefinitionFilter();
        qDebug() << "Creating a CppLibrary";
    };
    virtual ~CppLibrary() {}

    virtual QHash< QString, Grantlee::Filter* > filters(const QString& name = QString())
    {
        qDebug() << "Filter library is loaded, asking for filters";
        return m_filters;
    }
    
private:
    QHash<QString, Grantlee::Filter*> m_filters; 
};

#endif // CPPLIBRARY_H
