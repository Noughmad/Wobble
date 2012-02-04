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


#ifndef WOBBLE_OUTPUT_H
#define WOBBLE_OUTPUT_H

#include <QtCore/QObject>
#include <QtCore/QVariantMap>

#include "global.h"

namespace Wobble {

class Project;

class Class;

/**
 * @brief Interface class for all code outputs
 * 
 * Wobble uses a plugin architecture for reading and generating code. 
 * This is the base class for all code genetators. 
 * 
 * Every subclass must implement the name and write methods. 
 * 
 * @sa write
 **/
class WOBBLE_EXPORT Output : public QObject
{
public:
    explicit Output(QObject* parent = 0);
    virtual ~Output();
    
    virtual QByteArray name() = 0;
    /**
     * @brief Write out the @p project
     * 
     * The main method an output has to implement. The output should
     * write out the entire project structure, which is available via
     * calls to Project::members() and Project::findMember()
     *
     * @param project The project to write
     * @param options Plugin-specific options
     * @return true if the project code was generater successfully, false otherwise
     **/
    virtual bool write(const Project* project, QVariantMap options) = 0;
    
    /**
     * @brief Report the current progress status to Wobble
     * 
     * Using this function in not necessary, but it is recommended as 
     * it give the application user useful information. 
     *
     * @param done the number of units processed so far
     * @param total an estimated total number of units required
     * @param status on optional descriptive status of the output
     **/
    void setProgress(int done, int total, const QString& status = QString());
};

}

Q_DECLARE_INTERFACE(Wobble::Output, "eu.Noughmad.Wobble.Output/1.0")

#endif // WOBBLE_OUTPUT_H
