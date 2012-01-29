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

#ifndef WOBBLE_FUNCTION_H
#define WOBBLE_FUNCTION_H

#include "identifier.h"

namespace Wobble {
    
class FunctionPrivate;

W_FORWARD(Type)
W_FORWARD(Variable)

class WOBBLE_EXPORT Function : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(VariableList arguments READ arguments WRITE setArguments)
    Q_PROPERTY(Type* returnType READ returnType WRITE setReturnType)
    
public:
    Function(const QString& name, Type* type, Identifier* parent = 0);
    virtual ~Function();
    
    /**
     * @property type
     * 
     * The return type of this function. 
     *
     * Not all languages require a function to have a predetermined type, 
     * but Wobble does. 
     * 
     **/
    Type* returnType() const;
    void setReturnType(Type* type);

    /**
     * @property arguments
     *
     * The list of arguments to this function. 
     * 
     **/
    VariableList arguments() const;
    void setArguments(const VariableList& arguments);

    /**
     * @brief Adds an argument to this function
     *
     * @param argument The new argument
     **/
    void addArgument(Variable* argument);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Function)
};

W_DECLARE_POINTER(Function)

}

W_DECLARE_METATYPE(Function)

#endif // WOBBLE_FUNCTION_H
