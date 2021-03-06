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

class Resource;
class ProjectPrivate;

/**
 * @brief A complete top-level project
 * 
 * This class represents a programming project. It contains global options, 
 * such as the project type, external dependencies and use Wobble components. 
 * 
 * All identifiers within the project can be accessed via members()
 * 
 * @sa Input::read, Output::write, Identifier::members()
 **/
class WOBBLE_EXPORT Project : public Identifier
{
    Q_OBJECT
    Q_ENUMS(Component)
    Q_FLAGS(Components)
    Q_ENUMS(ProjectType)
 //   Q_PROPERTY(Compoents components READ components WRITE setComponents)
    Q_PROPERTY(ProjectType projectType READ projectType WRITE setProjectType)
    Q_PROPERTY(QString version READ version WRITE setVersion)
    Q_PROPERTY(QString license READ license WRITE setLicense)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(Resource* icon READ icon WRITE setIcon)
    Q_PROPERTY(bool notifier READ hasNotifier WRITE setNotifier)
    Q_PROPERTY(View* mainWindow READ mainWindow WRITE setMainWindow)

public:
    enum Component
    {
        Database = 0x01,
        UserInterface = 0x02,
        OpenGL = 0x04
    };
    Q_DECLARE_FLAGS(Components, Component)
    
    /**
     * Enumerates different project types
     **/
    enum ProjectType
    {
        Application, /**< A program or a website, capable of running on its own */
        Library /**< A library with a public API that can be used to build other programs */
    };
    
    Project();
    virtual ~Project();
    
    /**
     * @property projectType
     * @brief The type of this project
     * 
     * @sa ProjectType
     * 
     **/
    ProjectType projectType() const;
    void setProjectType(ProjectType type);

    /**
     * @property license
     *
     * The terms this project is licensed under.
     * Usually, this text will appear in the headers of all source files
     *
     **/
    QString license() const;
    void setLicense(const QString& license);

    /**
     * @property description
     *
     * A short description of the project
     *
     **/
    QString description() const;
    void setDescription(const QString& description);
    
    /**
     * @property icon
     *
     * The application icon, not required for libraries.
     *
     **/
    Resource* icon() const;
    void setIcon(Resource* icon);

    /**
     * @property notifier
     *
     * If true, the application will permanently show an icon in the
     * status area.
     *
     * Programs that have a notifier can still hide or show it at any time
     * using the Command::ShowNotifier and Command::HideNotifier command.
     *
     **/
    bool hasNotifier() const;
    void setNotifier(bool notifier);

    /**
     * @property mainWindow
     *
     * The main application window (if one exists).
     *
     * In desktop/mobile applications, this window is shown at program startup.
     * If the project has a notifier icon, Wobble initializes it in this class.
     *
     * In web application, this view is displayed as the home page.
     **/

    View* mainWindow() const;
    void setMainWindow(View* window);

    /**
     * @property version
     *
     * The version number of the project.
     * It can be an arbitrary string, not necessarily a number. 
     * 
     **/

    QString version() const;
    void setVersion(const QString& version);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Project)
};

W_DECLARE_POINTER(Project)

}

W_DECLARE_METATYPE(Project)

#endif // WOBBLE_IDENTIFIER_H
