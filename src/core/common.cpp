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

#include "common.h"

#include "identifier.h"
#include "type.h"
#include "class.h"
#include "variable.h"
#include "view.h"

#include <QMetaType>

using namespace Wobble;

View* Common::detailView()
{
    return 0;
}

View* Common::listDetailView()
{
    return 0;
}

View* Common::listView()
{
    return 0;
}

void Common::registerTypes()
{
    qRegisterMetaType<Identifier*>("Identifier*");
    qRegisterMetaType<Type*>("Type*");
    qRegisterMetaType<View*>("View*");
    qRegisterMetaType<Class*>("Class*");
    qRegisterMetaType<ClassList>("ClassList");
    qRegisterMetaType<Variable*>("Variable*");
    qRegisterMetaType<VariableList>("VariableList");
    qRegisterMetaType<Query*>("Query*");
    qRegisterMetaType<QueryList>("QueryList");
}

View* Common::classView(Class* c, bool editable)
{
    /*
     * TODO: This may be unnecessary, or at least move to Outputs. 
     * For example, Django has a ModelForm, maybe other tookits
     * have similar functionality. 
     */
    View* view = new View(c->name() + "View", c->topLevel());
    foreach (Variable* var, c->findChildren<Variable*>())
    {
        view->addSubView(variableView(var));
    }
    return view;
}

View* Common::variableView(Variable* var, bool editable)
{
    // TODO: Discover the appropriate StandardView from the variable's type
    View* v = new View(var->name() + "VariableView", var->topLevel());
    v->setViewType(View::LineView);
    return v;
}


