#ifndef WOBBLE_CLASSPRIVATE_H
#define WOBBLE_CLASSPRIVATE_H

#include "type_p.h"

#include <QList>


namespace Wobble {
    
    class Class;

class ClassPrivate : public TypePrivate
{

public:
    ClassPrivate(const QString& name, Identifier* space);
    virtual ~ClassPrivate();
    QList< Class* > superclasses;
    int features;
};

}

#endif // WOBBLE_CLASSPRIVATE_H
