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

#include "command.h"
#include "command_p.h"

#include "variable.h"

using namespace Wobble;

CommandPrivate::CommandPrivate(const QString& name, Type* type) : IdentifierPrivate(name)
{
    this->returnType = type;
}

Wobble::CommandPrivate::~CommandPrivate()
{

}

Command::Command(const QString& name, Type* type, Identifier* parent): Identifier(*new CommandPrivate(name, type), parent)
{
    
}

Command::Command(CommandPrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Command::~Command()
{

}

Type* Command::returnType() const
{
    Q_D(const Command);
    return d->returnType;
}

void Command::setReturnType(Type* type)
{
    Q_D(Command);
    d->returnType = type;
}

VariableList Command::arguments() const
{
    Q_D(const Command);
    return d->arguments;
}

void Command::setArguments(const Wobble::VariableList& arguments)
{
    Q_D(Command);
    d->arguments = arguments;
}

void Command::addArgument(Variable* argument)
{
    Q_D(Command);
    d->arguments << argument;
}

void Command::addArgument(QString name, Type* type)
{
    addArgument(new Variable(name, type, this));
}

#include "command.moc"
