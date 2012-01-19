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

#include "../core/config.h"

#include <grantlee/templateloader.h>
#include <grantlee/engine.h>

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
    engine = new Grantlee::Engine();
    engine->addPluginPath(TemplateFilterDir);
    
    Grantlee::FileSystemTemplateLoader::Ptr loader = Grantlee::FileSystemTemplateLoader::Ptr( new Grantlee::FileSystemTemplateLoader() );
    loader->setTemplateDirs( QStringList() << TemplateDir );
    engine->addTemplateLoader( loader );
}

TemplatesPrivate::~TemplatesPrivate()
{
    delete engine;
}

Grantlee::Engine* Templates::engine()
{
    return self()->engine;
}

Grantlee::Template Templates::getTemplate(const QString& name)
{
    return self()->engine->loadByName(name);
}






