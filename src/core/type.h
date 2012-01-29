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

#ifndef WOBBLE_TYPE_H
#define WOBBLE_TYPE_H

#include "identifier.h"

namespace Wobble {
    
class TypePrivate;

/**
 * @brief An object that represents a variable type
 * 
 * 
 **/
class WOBBLE_EXPORT Type : public Identifier
{
    Q_OBJECT
    Q_ENUMS(Source)
    Q_PROPERTY(Source source READ source WRITE setSource)
    Q_ENUMS(StandardType)
    Q_PROPERTY(StandardType standardType READ standardType WRITE setStandardType)
    Q_PROPERTY(bool pod READ isPod WRITE setPod)
    Q_PROPERTY(bool object READ isObject WRITE setObject)
    Q_PROPERTY(Type* valueType READ valueType WRITE setValueType)
    Q_PROPERTY(Type* keyType READ keyType WRITE setKeyType)
    
public:
    enum Source
    {
        BuiltIn,
        External,
        Project
    };
    
    /**
     * @brief Names of common built-in types
     * 
     * This enum holds types that are common to (almost) all languages. 
     * 
     * It includes types that are not necessarily present in the languages, 
     * but are supported by widely-used libraries, such as DateTime. 
     * 
     * @sa standardType()
     **/
    enum StandardType
    {
        Character, /**< The character type, usually one byte long */
        String, /**< The basic string type */
        Boolean, /**< The boolean type, holding either true or false */
        Integer, /**< The basic integer type */
        Float, /**< The floating point number type */
        DateTime, /**< A type holding a point in time */
        File, /**< A file */
        List, /**< A list of values. Must have valueType set */
        Map, /**< A map or dictionary of keys and values. Must have valueType and keyType set */
        Custom /**< None of the above, a non-standard type */
    };
    
    /**
     * @brief Default constructor
     * 
     * Constructs a type with name @p name and namespace @p parent. 
     * 
     * Use this constructor only if your project defines new types that
     * are not classes. For defining classes, use Class directly. 
     * For using common data type, use standardType(). 
     * 
     * @param name name of this type
     * @param parent parent namespace
     **/
    Type(const QString& name, Identifier* parent = 0);
    virtual ~Type();
    
    /**
     * @brief Creates a Type object for a common built-in datatype. 
     * 
     * This is the preferred method for accessing common type. 
     * Different languages have different methods for these type, so
     * it is the Input's task to convert them to StandardType, and
     * the Output's task to give the appropriate name. 
     * 
     * Standard types are always created as top-level identifiers, 
     * so they have no parent and can't be accessed by
     * traversing the identifier tree. However, they are owned
     * by Wobble, so never delete the objects returned by these functions. 
     * 
     * @note Don't use this function to create list or map types, 
     * instead use list() or map(), respectively. 
     *
     * @sa StandardType
     * @return Type*
     **/
    static Type* fromStandardType(StandardType type);
    static Type* list(Type* values);
    static Type* map(Type* keys, Type* values);
    static Type* findByName(const QString& name);
    
    /**
     * Returns a common name associated with the standard @p type. 
     * 
     * In most cases, the names are taken from the C type, as
     * those are often the shortest and universally recognised. 
     **/
    static QString standardTypeName(StandardType type);
    
    Source source() const;
    void setSource(Source source);
    
    /**
     * @property object
     *
     * Holds whether this type is an object class. 
     * Objects are always passed with pointer. 
     * 
     * @note Some output languages may not differentiate 
     * between object and non-object types. 
     **/
    bool isObject() const;
    void setObject(bool object);
    
    /**
     * @property pod
     *
     * Holds whether this is a "plain old data" type. 
     * This is true for most core data types like integers, but not for
     * complex data structures like strings or lists. 
     * 
     * POD values are passed by value by default. 
     * 
     * @note Some output languages may not differentiate 
     * between POD and non-POD types. 
     **/
    bool isPod() const;
    void setPod(bool pod);
    
    /**
     * @property valueType
     *
     * If this is a list type, this property holds the type 
     * of each element in the list. 
     * 
     * If this is a map type, this property holds the type
     * of map values. 
     * 
     * Otherwise, valueType is 0. 
     * 
     **/
    Type* valueType() const;
    void setValueType(Type* valueType);
    
    /**
     * @property keyType
     *
     * If this is a map type, this property holds the type
     * of map key. Note that while Wobble allows you to use 
     * any type as keyType, languages may impose additional
     * restraints. 
     * 
     * If this is not a map, keyType is 0. 
     * 
     **/
    Type* keyType() const;
    void setKeyType(Type* keyType);

    /**
     * @property standardType
     *
     * @sa StandardType
     * 
     **/
    StandardType standardType() const;
    void setStandardType(StandardType type);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Type)
};

W_DECLARE_POINTER(Type)

}

W_DECLARE_METATYPE(Type)

#endif // WOBBLE_TYPE_H
