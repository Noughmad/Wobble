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

#include "command.h"

namespace Wobble {
    
class FunctionPrivate;

W_FORWARD(Type)
W_FORWARD(Variable)

class WOBBLE_EXPORT Function : public Command
{
    Q_OBJECT
    Q_PROPERTY(CommandList commands READ commands WRITE setCommands)
    
public:
    Function(const QString& name, Type* type, Identifier* parent = 0);
    virtual ~Function();
    
    /**
     * @property commands
     *
     * The list of commands that form the body of this function
     * 
     **/
    CommandList commands() const;
    void setCommands(const CommandList& commands);

    /**
     * @brief Add a command to this function's body
     *
     * @param command The new command
     **/
    void addCommand(Command* command);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Function)
};

W_DECLARE_POINTER(Function)

}

W_DECLARE_METATYPE(Function)

#endif // WOBBLE_FUNCTION_H
