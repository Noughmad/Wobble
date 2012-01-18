#ifndef WOBBLE_VARIABLE_H
#define WOBBLE_VARIABLE_H

#include "identifier.h"

namespace Wobble {
    
class VariablePrivate;
class Class;
class Type;

class Variable : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(Type type READ type WRITE setType)
    
public:
    Variable(const QString& name, Type* type, Identifier* space = 0, QObject* parent = 0);
    Variable(Class* cls);

protected:
    Variable(VariablePrivate& dd, QObject* parent = 0);

public:
    virtual ~Variable();
};

}

#endif // WOBBLE_VARIABLE_H
