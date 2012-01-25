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

#ifndef WOBBLE_VISITOR_H
#define WOBBLE_VISITOR_H

#include "global.h"

namespace Wobble {

class Project;
class Class;
class Type;
class Identifier;
class Variable;
class Query;
class View;

class WOBBLE_EXPORT Visitor
{
    
public:
    virtual ~Visitor();

    virtual void visit(Project* project) = 0;
    virtual void visit(Type* type) = 0;
    virtual void visit(Variable* var) = 0;
    virtual void visit(Class* cls) = 0;
    virtual void visit(Query* query) = 0;
    virtual void visit(View* view) = 0;
    virtual void visit(Identifier* identifier) = 0;
};

}

#endif // WOBBLE_VISITOR_H
