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

#ifndef WOBBLE_IDENTIFIER_H
#define WOBBLE_IDENTIFIER_H

#include <QObject>
#include <QVariantMap>
#include <QtCore/QString>

#include "global.h"
#include "visitor.h"

#include <QDebug>

/**
 * @brief Main namespace for all Wobble classes
 **/
namespace Wobble {

/// @internal
class IdentifierPrivate;

W_FORWARD(Identifier)

/**
 * @brief Base class for all Wobble code objects
 * 
 * An Identifier represents the most basic object in all languages. 
 * It only requires a name and a parent identifier (a class, namespace or function). 
 * 
 * Every identifier requires a name, but can be given a null parent so that 
 * it is a top-level identifier. 
 **/
class WOBBLE_EXPORT Identifier : public QObject
{
    Q_OBJECT
    Q_ENUMS(AccessType)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Identifier* space READ space WRITE setSpace STORED false)
    Q_PROPERTY(QString documentation READ documentation WRITE setDocumentation)
    Q_PROPERTY(AccessType accessType READ accessType WRITE setAccessType)
    Q_PROPERTY(IdentifierList members READ members)
    Q_PROPERTY(bool local READ isLocal WRITE setLocal)
    
public:
    /**
     * Describes the access type (private, protected or public) of this identifier
     */
    enum AccessType
    {
        Public, /**< This identifier is only accessible directly from its parent class */
        Protected, /**< This identifier is accessible from the parent class and all its subclasses */
        Private /**< This identifier is accessible from anywhere */
    };
    
    /**
     * @brief Default constructor
     * 
     * Constructs an Identifier with name @p name in namespace @p space. 
     * 
     * \sa name, space
     *
     * @param name the identifier name
     * @param parent the containing namespace.
     **/
    Identifier(const QString& name, Identifier* parent = 0);
    /**
     * @brief Default destructor
     *
     **/
    virtual ~Identifier();
    
    /**
     * @property name
     * @brief The name of this identifier
     * 
     * It does not have to be globally unique, only within the same namespace. 
     * Wobble will enforce this limitation.
     **/
    QString name() const;
    void setName(const QString& name);
    
     /**
     * @property space
     * @brief The parent namespace of this identifier
     **/
    Identifier* space() const;
    void setSpace(Wobble::Identifier* space);
    
    /**
     * @property documentation
     * @brief A docstring for this identifier
     *
     **/
    QString documentation() const;
    void setDocumentation(const QString& documentation);
    
    /** 
     * @property accessType
     * 
     * The access type of this identifier. 
     * By default, all identifiers are public. 
     * 
     * @sa AccessType
     */
    AccessType accessType() const;
    void setAccessType(AccessType accessType);
    
    /**
     * @brief Returns the fully-qualified name of this identifier
     *
     * @param separator a string with which to separate namespaces, for example "::" or "."
     * @return QString
     **/
    QString fullName(const QString& separator) const;
    
    /**
     * @brief The top-level identifier
     *
     * @return :Identifier*
     **/
    Identifier* topLevel();
    
    /**
     * @brief Returns the list of members
     * 
     * Returns the list of all members of this identifier, 
     * i.e. all identifiers with this as their namespace. 
     **/
    IdentifierList members() const;

    /**
     * @property local
     *
     * Specifies whether this identifier comes from the current project.
     *
     * Default is true. 
     * 
     **/
    bool isLocal() const;
    void setLocal(bool local);

    template < class T >
    QList<T> findMembers(const QString& name = QString()) const;
    
    /**
     * Tries to find a member of type @p T with name @p name. 
     * If no such member is found, a new one is created. 
     *
     * @param T The type of the member to look for or create, 
     * should inherit Identifier
     * @param name The member name
     * @return T*
     **/
    template < class T>
    T* findOrCreateMember(const QString& name);
        
//    virtual QVariantMap serialize() const;

    W_ACCEPT_VISITOR
        
protected:
    IdentifierPrivate* const d_ptr;
    W_DECLARE_PRIVATE(Identifier)
};

template < class T>
T* Identifier::findOrCreateMember(const QString& name)
{
    T* ret = findChild<T*>(name);
    if (ret)
    {
        return ret;
    }
    
    return new T(name, this);
}

template < class T >
QList< T > Identifier::findMembers(const QString& name) const
{
    QList<T> ret;
    foreach (Identifier* id, members())
    {
        if (T t = qobject_cast<T>(id))
        {
            ret << t;
        }
    }
    return ret;
}


W_DECLARE_POINTER(Identifier)

}

W_DECLARE_METATYPE(Identifier)
    

WOBBLE_EXPORT QDebug& operator<<(QDebug& stream, Wobble::Identifier* id);

#endif // WOBBLE_IDENTIFIER_H
