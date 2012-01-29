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

#include "query.h"
#include "query_p.h"

using namespace Wobble;

QueryPrivate::QueryPrivate(const QString& name, Type* type) : IdentifierPrivate(name)
{
    this->type = type;
}

Wobble::QueryPrivate::~QueryPrivate()
{

}

Query::Query(const QString& name, Type* type, Identifier* parent): Identifier(*new QueryPrivate(name, type), parent)
{
    
}

Query::Query(QueryPrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Query::~Query()
{

}

void Query::setType(Type* type)
{
    Q_D(Query);
    d->type = type;
}

Type* Query::type() const
{
    Q_D(const Query);
    return d->type;
}

Query::QueryType Query::queryType() const
{
    Q_D(const Query);
    return (QueryType)d->queryType;
}

void Query::setQueryType(Query::QueryType queryType)
{
    Q_D(Query);
    d->queryType = (int)queryType;
}

int Query::limit() const
{
    Q_D(const Query);
    return d->limit;
}

void Query::setLimit(int limit)
{
    Q_D(Query);
    d->limit = limit;
}

QList< Query::Filter > Query::filters() const
{
    Q_D(const Query);
    return d->filters;
}

void Query::setFilters(const QList< Query::Filter > filters)
{
    Q_D(Query);
    d->filters = filters;
}

void Query::addFilter(const Query::Filter& filter)
{
    Q_D(Query);
    d->filters.append(filter);
}

#include "query.moc"
