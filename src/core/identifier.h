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


/**
 * @brief Main namespace for all Wobble classes
 **/
namespace Wobble {

class IdentifierPrivate;

/**
 * @brief Base class for all Wobble code objects
 * 
 * An Identifier represents the most basic object is all languages. 
 * It only requires a name and a parent identifier (a class, namespace or function). 
 * 
 * Every identifier requires a name, but can be given a null parent so that 
 * it is a top-level identifier. 
 **/
class Identifier : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Identifier* space READ space WRITE setSpace)
    
public:
    /**
     * @brief Default constructor
     * 
     * Constructs an Identifier with name @p name in namespace @p space. 
     * 
     * \sa name, space
     *
     * @param name the identifier name
     * @param space the containing namespace. If 0 is given, this creates a top-level identifier. Defaults to 0.
     * @param parent parent QObject.
     **/
    Identifier(const QString& name, Identifier* space = 0, QObject* parent = 0);
    /**
     * @brief Default destructor
     *
     **/
    virtual ~Identifier();
    
    QString fullName(const QString& separator) const;
    
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
     * @brief The namespace of this identifier
     **/
    Identifier* space() const;
    void setSpace(Identifier* space);
    
    /**
     * @brief Returns the list of members
     * 
     * Returns the list of all members of this identifier, 
     * i.e. all identifiers with this as their namespace. 
     **/
    QList<Identifier*> members() const;
    
    virtual QVariantMap serialize() const;
        
protected:
    IdentifierPrivate* const d_ptr;
    Identifier(IdentifierPrivate& dd, QObject* parent = 0);
    
private:
    Q_DECLARE_PRIVATE(Identifier)
};

}

#endif // WOBBLE_IDENTIFIER_H
