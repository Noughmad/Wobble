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

#ifndef WOBBLE_QUERY_H
#define WOBBLE_QUERY_H

#include "identifier.h"

namespace Wobble {

class Variable;
    
class QueryPrivate;

W_FORWARD(Type)

/**
 * @brief A database query
 * 
 * Represents a database query that provides data to classes or views. 
 **/
class WOBBLE_EXPORT Query : public Identifier
{
    Q_OBJECT
    Q_ENUMS(QueryType)
    Q_PROPERTY(Type* type READ type WRITE setType)
    Q_PROPERTY(QueryType queryType READ queryType WRITE setQueryType)
    Q_PROPERTY(int limit READ limit WRITE setLimit)
    Q_PROPERTY(QList<Filter> filters READ filters WRITE setFilters)
    
public:
    /**
     * Different types of database queries
     **/
    enum QueryType
    {
        GetOne, /**< The query returns exactly one item from the database */
        GetMany, /**< The query may return any number of items */
        GetCount, /**< The query returns the number of matching items */
        Read = 0x10, /**< Not used directly, query types below that are read-only */
        Insert, /**< The query inserts rows into the database.  */
        Update, /**< The query updates existing items */
        Write = 0x20, /**< Not used directly, query types below that don't delete anything */
        Delete /**< The query removes items from the database */
    };
    
    /**
     * Supported filter operation in WHERE clauses. 
     **/
    enum FilterType
    {
        None,
        Equals,
        NotEquals,
        GreaterThan,
        LessThan,
        GreaterOrEquals,
        LessOrEquals,
        StartsWith,
        EndsWith,
        Contains,
        IsIn
    };
    
    /**
     * @brief A query filter
     * 
     * For example, if operation is Equals, this will produce code similar to 
     * 
     * @code
     * WHERE var->name() EQUALS value
     * @endcode
     * 
     * However, it is the output's responsibility to translate a Filter to code, 
     * as well as take any safety precaucions to prevent injections. 
     * 
     **/
    struct Filter
    {
        /**
         * @brief The variable used for matching
         * 
         * Generally, only the variable name is required, 
         * but the output may make use of knowing its type as well. 
         **/
        Variable* var;
        
        /**
         * @brief The filtering operation
         * 
         * @sa FilterType
         **/
        FilterType operation;
        /**
         * @brief The value to match
         **/
        QString value;
    };
    
    /**
     * @brief Default constructor
     * 
     * Contructs a query with a set name and type, but with no filters. 
     * By default, this query will return all items of the specified @p type. 
     *
     * @param name The query name, will also be the name of the returned variable. 
     * @param type The expected result type
     * @param parent The containing namespace.
     **/
    Query(const QString& name, Type* type, Identifier* parent = 0);
    /**
     * @brief Default destructor
     *
     **/
    virtual ~Query();
    
    /**
     * @property type
     * 
     * The type of this query's result. 
     *
     * Not all languages and/or database engines 
     * require a query to have a predetermined type, 
     * but Wobble does. 
     * 
     **/
    Type* type() const;
    void setType(Type* type);
    
    /**
     * @property queryType
     *
     * The type of this query
     *
     * @sa QueryType
     * 
     **/
    QueryType queryType() const;
    void setQueryType(QueryType queryType);
    
    int limit() const;
    void setLimit(int limit);
    
    QList<Filter> filters() const;
    void setFilters(const QList<Filter> filters);
    void addFilter(const Filter& filter);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Query)
};

W_DECLARE_POINTER(Query)

}

W_DECLARE_METATYPE(Query)

#endif // WOBBLE_QUERY_H
