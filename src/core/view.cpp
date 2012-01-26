#include "view.h"
#include "view_p.h"
#include "type.h"
#include "class.h"
#include "variable.h"

using namespace Wobble;

ViewPrivate::ViewPrivate(const QString& name) : IdentifierPrivate(name)
{

}

ViewPrivate::~ViewPrivate()
{

}

View::View(const QString& name, Identifier* parent): Identifier(*new ViewPrivate(name), parent)
{

}

View::View(Wobble::ViewPrivate& dd, QObject* parent): Identifier(dd, parent)
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

Type* View::model() const
{
    Q_D(const View);
    return d->model;
}

void View::setModel(Type* model)
{
    Q_D(View);
    d->model = model;
}

View* View::fromType(Type* type)
{
    View* v = new View(type->name() + "-view", type->space());
    if (type->standardType() != Type::Custom)
    {
        // TODO: Use a mapping from standard types to standard views
        // Or maybe even just store the StandardType and rely on outputs to create the proper view
        
    }
    else if (Class* c = qobject_cast<Class*>(type))
    {
        foreach (Variable* var, c->findMembers<Variable*>())
        {
            v->addSubView(fromType(var->type()));
        }
    }
    return v;
}


#include "view.moc"