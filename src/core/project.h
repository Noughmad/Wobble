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

#ifndef WOBBLE_PROJECT_H
#define WOBBLE_PROJECT_H

#include "identifier.h"

namespace Wobble {

class ProjectPrivate;

class Project : public Identifier
{
    Q_OBJECT
    Q_ENUMS(Component)
    Q_FLAGS(Components)
    Q_ENUMS(ProjectType)
    Q_PROPERTY(Compoents components READ components WRITE setComponents)
    Q_PROPERTY(ProjectType type READ type WRITE setType)

public:
    enum Component
    {
        Database = 0x01,
        UserInterface = 0x02,
        OpenGL = 0x04
    };
    Q_DECLARE_FLAGS(Components, Component)
    
    enum ProjectType
    {
        Application,
        Library
    };
    
    Project();
    virtual ~Project();

protected:
    ProjectPrivate* const d_ptr;
    Project(ProjectPrivate& dd, QObject* parent = 0);

private:
    Q_DECLARE_PRIVATE(Project)
};

}

#endif // WOBBLE_IDENTIFIER_H
