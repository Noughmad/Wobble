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

#include "function.h"
#include "function_p.h"

using namespace Wobble;

FunctionPrivate::FunctionPrivate(const QString& name, Type* type) : IdentifierPrivate(name)
{
    this->type = type;
}

Wobble::FunctionPrivate::~FunctionPrivate()
{

}

Function::Function(const QString& name, Type* type, Identifier* parent): Identifier(*new FunctionPrivate(name, type), parent)
{
    
}

Function::Function(FunctionPrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Function::~Function()
{

}

Type* Function::returnType() const
{
    Q_D(const Function);
    return d->returnType;
}

void Function::setReturnType(Type* type)
{
    Q_D(Function);
    d->returnType = type;
}

VariableList Function::arguments() const
{
    Q_D(const Function);
    return d->arguments;
}

void Function::setArguments(const Wobble::VariableList& arguments)
{
    Q_D(Function);
    d->arguments = arguments;
}

void Function::addArgument(Variable* argument)
{
    Q_D(Function);
    d->arguments << argument
}



#include "function.moc"
