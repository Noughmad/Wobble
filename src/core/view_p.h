#ifndef WOBBLE_VIEWPRIVATE_H
#define WOBBLE_VIEWPRIVATE_H

#include "class_p.h"

namespace Wobble {
    
class View;

W_FORWARD(Query)

class ViewPrivate : public ClassPrivate
{

public:
    ViewPrivate(const QString& name);
    virtual ~ViewPrivate();
    
    QList<View*> subViews;
    QueryList queries;
    bool editable;
    int viewType;
};

}

#endif // WOBBLE_VIEWPRIVATE_H
