#ifndef WOBBLE_CLASSPRIVATE_H
#define WOBBLE_CLASSPRIVATE_H

#include "type_p.h"

#include <QList>


namespace Wobble {
    
    W_FORWARD(Class)

class ClassPrivate : public TypePrivate
{

public:
    ClassPrivate(const QString& name);
    virtual ~ClassPrivate();
    ClassList superclasses;
    int features;
};

}

#endif // WOBBLE_CLASSPRIVATE_H
