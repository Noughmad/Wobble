#include "view.h"
#include "view_p.h"

using namespace Wobble;

ViewPrivate::ViewPrivate(const QString& name, Identifier* space) : ClassPrivate(name, space)
{

}

ViewPrivate::~ViewPrivate()
{

}

View::View(const QString& name, Wobble::Identifier* space, QObject* parent): Class(name, space, parent)
{

}

View::View(Wobble::ViewPrivate& dd, QObject* parent): Class(dd, parent)
{

}

View::~View()
{

}

#include "view.moc"