#include "view.h"
#include "view_p.h"

using namespace Wobble;

ViewPrivate::ViewPrivate(const QString& name) : ClassPrivate(name)
{

}

ViewPrivate::~ViewPrivate()
{

}

View::View(const QString& name, Identifier* parent): Class(name, parent)
{

}

View::View(Wobble::ViewPrivate& dd, QObject* parent): Class(dd, parent)
{

}

View::~View()
{

}

#include "view.moc"