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


#ifndef WOBBLE_INPUT_H
#define WOBBLE_INPUT_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include "global.h"

namespace Wobble {

class Project;

class WOBBLE_EXPORT Input : public QObject
{
public:
    explicit Input(QObject* parent = 0);
    virtual ~Input();
    
    virtual QByteArray name() = 0;
    virtual bool read(Project* project, QVariantMap options) = 0;
};

}

Q_DECLARE_INTERFACE(Wobble::Input, "eu.Noughmad.Wobble.Input/1.0")

#endif // WOBBLE_INPUT_H
