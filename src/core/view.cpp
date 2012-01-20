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

bool View::isEditable() const
{
    Q_D(const View);
    return d->editable;
}

void View::setEditable(bool editable)
{
    Q_D(View);
    d->editable = editable;
}

View::StandardView View::viewType() const
{
    Q_D(const View);
    return (StandardView)d->viewType;
}

void View::setViewType(View::StandardView viewType)
{
    Q_D(View);
    d->viewType = viewType;
}

QueryList View::queries() const
{
    Q_D(const View);
    return d->queries;
}

void View::addQuery(Query* query)
{
    Q_D(View);
    d->queries << query;
}

QList< View* > View::subViews() const
{
    Q_D(const View);
    return d->subViews;
}

void View::addSubView(View* view)
{
    Q_D(View);
    d->subViews << view;
}

View* View::listItem() const
{
    Q_D(const View);
    return d->listItem;
}

void View::setListItem(View* listItem)
{
    Q_D(View);
    d->listItem = listItem;
}

#include "view.moc"