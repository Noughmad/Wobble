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

#ifndef WOBBLE_COMMAND_H
#define WOBBLE_COMMAND_H

#include "identifier.h"

namespace Wobble {
    
class CommandPrivate;

W_FORWARD(Type)
W_FORWARD(Variable)

class WOBBLE_EXPORT Command : public Identifier
{
    Q_OBJECT
    Q_ENUMS(StandardCommand)
    Q_PROPERTY(VariableList arguments READ arguments WRITE setArguments)
    Q_PROPERTY(Type* returnType READ returnType WRITE setReturnType)
    Q_PROPERTY(StandardCommand standardCommand READ standardCommand)
    
public:

    /**
    * @brief A set of standard commands
    *
    * These commands should be available on every platform, so it's preferred
    * to use them over custom functions.
    *
    **/
    enum StandardCommand {
        Custom,
        New,
        Open,
        Save,
        SaveAs,
        
        ShowNotifier,
        HideNotifier,
        ShowNotification,
        ShowDialog,
        PlaySound,
        OpenExternalProgram,

        CreateObject,
        DestroyObject,
        RunQuery,
        
        Quit
    };
  
    Command(const QString& name, Type* type, Identifier* parent = 0);
    Command(StandardCommand standardCommand, VariableList arguments, Identifier* parent = 0);
    virtual ~Command();
    
    /**
     * @property type
     * 
     * The return type of this command. 
     *
     * Not all languages require a command to have a predetermined type, 
     * but Wobble does. 
     * 
     **/
    Type* returnType() const;
    void setReturnType(Type* type);

    /**
     * @property arguments
     *
     * The list of arguments to this command. 
     * 
     **/
    VariableList arguments() const;
    void setArguments(const VariableList& commands);

    /**
     * @brief Add an argument to this command
     *
     * @param argument The new argument
     **/
    void addArgument(Variable* argument);
    
    /**
     * Add an argument with name @p name and type @p type. 
     *
     * @param name the name of the new argument
     * @param type the type of the new argument
     * @return void
     **/
    void addArgument(QString name, Type* type);


    /**
     * @property standardCommand
     *
     * Holds the standard command type of this command.
     * For custom commands, the values is Custom. 
     */
    StandardCommand standardCommand() const;

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Command)
};

W_DECLARE_POINTER(Command)

}

W_DECLARE_METATYPE(Command)

#endif // WOBBLE_COMMAND_H
