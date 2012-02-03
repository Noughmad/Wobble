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

#include "project.h"
#include "project_p.h"

using namespace Wobble;

ProjectPrivate::ProjectPrivate() : IdentifierPrivate(QString())
{
    
}

ProjectPrivate::~ProjectPrivate()
{
    
}


Project::Project() : Identifier(*new ProjectPrivate, 0)
{

}

Project::Project(ProjectPrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Project::~Project()
{

}

Project::ProjectType Project::projectType() const
{
    Q_D(const Project);
    return (ProjectType)d->type;
}

void Project::setProjectType(Project::ProjectType type)
{
    Q_D(Project);
    d->type = type;
}

QString Project::license() const
{
    Q_D(const Project);
    return d->license;
}

void Project::setLicense(const QString& license)
{
    Q_D(Project);
    d->license = license;
}

QString Project::description() const
{
    Q_D(const Project);
    return d->description;
}

void Project::setDescription(const QString& description)
{
    Q_D(Project);
    d->description = description;
}

Resource* Project::icon() const
{
    Q_D(const Project);
    return d->icon;
}

void Project::setIcon(Resource* icon)
{
    Q_D(Project);
    d->icon = icon;
}

bool Project::hasNotifier() const
{
    Q_D(const Project);
    return d->notifier;
}

void Project::setNotifier(bool notifier)
{
    Q_D(Project);
    d->notifier = notifier;
}

View* Project::mainWindow() const
{
    Q_D(const Project);
    return d->mainWindow;
}

void Project::setMainWindow(View* window)
{
    Q_D(Project);
    d->mainWindow = window;
}

QString Project::version() const
{
    Q_D(const Project);
    return d->version;
}

void Project::setVersion(const QString& version)
{
    Q_D(Project);
    d->version = version;
}

#include "project.moc"