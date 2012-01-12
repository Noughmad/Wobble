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


namespace Wobble {

class IdentifierPrivate;

class Identifier : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(Identifier* space READ space WRITE setSpace)
    
public:
    Identifier(const QString& name, Identifier* space = 0, QObject* parent = 0);
    virtual ~Identifier();
    
    QString fullName(const QString& separator) const;
    
    QString name() const;
    void setName(const QString& name);
    
    Identifier* space() const;
    void setSpace(Identifier* space);
    
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
