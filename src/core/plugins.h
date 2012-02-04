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

#ifndef WOBBLE_PLUGINS_H
#define WOBBLE_PLUGINS_H

#include "global.h"

#include <QList>
#include <QByteArray>

namespace Wobble {

class Input;
class Output;

/**
 * @brief Functions for querying and loading plugins
 * 
 * Both input and output plugins can be loaded directly,
 * when their name is known. 
 *
 * @code
 * Input* input = Plugins::loadInput("YAML");
 * @endcode
 *
 * Alternatively, a list of all available plugins can be retrieved from Wobble.
 * @code
 * foreach (const QByteArray& name, Plugins::availableOutputs())
 * {
 *      // Check if you want to use this plugin
 *      bool useful = ...
 *      if (!useful)
 *      {
 *          continue;
 *      }
 *      Output* output = Plugins::loadOutput(name);
 *      // Use the output
 *      output->write(project, options);
 * }
 * @endcode
 *
 * All plugins are loaded the first time any of the functions in this namespace are used, so
 * any calling it multiple times doesn't bring any significant performance penalty.
 * 
 **/
namespace Plugins
{
  /**
   * @brief Returns the list of available input plugins
   *
   * This function queries all available and loadable inputs
   * and returns their names.
   *
   * @sa Input::name()
   *
   * @return The list of available input names. 
   **/
  WOBBLE_EXPORT QList<QByteArray> availableInputs();

  /**
   * @brief Returns the list of available output plugins
   *
   * This function queries all available and loadable outputs
   * and returns their names.
   *
   * @sa Output::name()
   *
   * @return The list of available output names. 
   **/
  WOBBLE_EXPORT QList<QByteArray> availableOutputs();

  /**
   * Returns the input with name @p name.
   * If no such input is found, 0 is returned.
   *
   * @param name the name of the loaded input. 
   * @return The loaded input, or 0 if none is found. 
   **/
  WOBBLE_EXPORT Input* loadInput(const QByteArray& name);

  /**
   * Returns the output with name @p name.
   * If no such output is found, 0 is returned.
   *
   * @param name the name of the loaded output.
   * @return The loaded output, or 0 if none is found. 
   **/
  WOBBLE_EXPORT Output* loadOutput(const QByteArray& name);
}

}

#endif // WOBBLE_PLUGINS_H
