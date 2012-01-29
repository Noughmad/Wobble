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

#ifndef WOBBLE_COMMON_H
#define WOBBLE_COMMON_H

#include "global.h"
#include "type.h"

namespace Wobble {

class View;
class Type;
class Class;
class Variable;
    
namespace Common
{
    WOBBLE_EXPORT View* listView();
    WOBBLE_EXPORT View* detailView();
    
    WOBBLE_EXPORT View* listDetailView();
    
    WOBBLE_EXPORT View* standardTypeView(Type::StandardType type, bool editable = false);
    WOBBLE_EXPORT View* variableView(Variable* var, bool editable = false);
    WOBBLE_EXPORT View* classView(Class* c, bool editable = false);
    
    /**
     * Register all Wobble identifier types with the Qt metatype system
     * 
     * @sa qRegisterMetaType
     **/
    WOBBLE_EXPORT void registerTypes();
}

}

#endif // WOBBLE_COMMON_H
