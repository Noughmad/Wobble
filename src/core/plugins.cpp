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

#include "plugins.h"
#include "input.h"
#include "output.h"
#include "config.h"

#include <QMap>
#include <QFileInfo>
#include <QDir>
#include <QPluginLoader>

using namespace Wobble;

class PluginsPrivate
{
public:
  PluginsPrivate();
  
  QMap<QByteArray, Output*> outputs;
  QMap<QByteArray, Input*> inputs;
};

PluginsPrivate::PluginsPrivate()
{
    foreach (const QFileInfo& plugin, QDir(PluginDir).entryInfoList(QDir::Files))
    {
        QPluginLoader l(plugin.absoluteFilePath());
        if (Input* input = qobject_cast< Input* >(l.instance()))
        {
            inputs.insert(input->name(), input);
        }
        if (Output* output = qobject_cast< Output* >(l.instance()))
        {
            outputs.insert(output->name(), output);
        }
    }
}


Q_GLOBAL_STATIC(PluginsPrivate, self)

QList< QByteArray > Plugins::availableInputs()
{
    return self()->inputs.keys();
}

QList< QByteArray > Plugins::availableOutputs()
{
    return self()->outputs.keys();
}

Input* Plugins::loadInput(const QByteArray& name)
{
    return self()->inputs.value(name, 0);
}

Output* Plugins::loadOutput(const QByteArray& name)
{
    return self()->outputs.value(name, 0);
}
