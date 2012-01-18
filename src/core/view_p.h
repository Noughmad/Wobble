#ifndef WOBBLE_VIEWPRIVATE_H
#define WOBBLE_VIEWPRIVATE_H

#include "class_p.h"

namespace Wobble {
    
class View;

class ViewPrivate : public ClassPrivate
{

public:
    ViewPrivate(const QString& name);
    virtual ~ViewPrivate();
};

}

#endif // WOBBLE_VIEWPRIVATE_H
