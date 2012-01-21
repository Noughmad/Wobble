#ifndef WOBBLE_VIEWPRIVATE_H
#define WOBBLE_VIEWPRIVATE_H

#include "class_p.h"

namespace Wobble {

W_FORWARD(Query)
W_FORWARD(View)

class ViewPrivate : public IdentifierPrivate
{

public:
    ViewPrivate(const QString& name);
    virtual ~ViewPrivate();
    
    ViewList subViews;
    QueryList queries;
    bool editable;
    int viewType;
    View* listItem;
};

}

#endif // WOBBLE_VIEWPRIVATE_H
