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

#include "templates.h"

#include "../core/type.h"
#include "../core/class.h"
#include "../core/identifier.h"
#include "../core/variable.h"
#include "../core/project.h"
#include "../core/view.h"
#include "../core/common.h"

#include "../core/config.h"

#include <grantlee/templateloader.h>
#include <grantlee/engine.h>
#include <grantlee/metatype.h>

using namespace Wobble;

class TemplatesPrivate
{
public:
    TemplatesPrivate();
    virtual ~TemplatesPrivate();
    
    Grantlee::Engine* engine;
};

Q_GLOBAL_STATIC(TemplatesPrivate, self)

TemplatesPrivate::TemplatesPrivate()
{
    qDebug() << "Creating the template engine";
    engine = new Grantlee::Engine();
    engine->addPluginPath(TemplateFilterBaseDir);
    
    Grantlee::FileSystemTemplateLoader::Ptr loader = Grantlee::FileSystemTemplateLoader::Ptr( new Grantlee::FileSystemTemplateLoader() );
    loader->setTemplateDirs( QStringList() << TemplateDir );
    engine->addTemplateLoader( loader );
    
    Common::registerTypes();
    
    Grantlee::registerMetaType<Variable*>();
    Grantlee::registerMetaType<Type*>();
    Grantlee::registerMetaType<Class*>();
    Grantlee::registerMetaType<View*>();
    Grantlee::registerMetaType<Query*>();
}

TemplatesPrivate::~TemplatesPrivate()
{
    qDebug() << "Deleting the template engine";
    delete engine;
}

Grantlee::Engine* Templates::engine()
{
    return self()->engine;
}

Grantlee::Template Templates::getTemplate(const QString& name)
{
    Grantlee::Template t = self()->engine->loadByName(name);
    qDebug() << name << t->nodeList().size();
    if (t->error() != Grantlee::NoError)
    {
        qDebug() << t->errorString();
    }
    return t;
}






