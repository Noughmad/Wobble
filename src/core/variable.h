#ifndef WOBBLE_VARIABLE_H
#define WOBBLE_VARIABLE_H

#include "identifier.h"

namespace Wobble {
    
class VariablePrivate;

W_FORWARD(Type)

class WOBBLE_EXPORT Variable : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(Type* type READ type WRITE setType)
    
public:
    Variable(const QString& name, Type* type, Identifier* parent = 0);
    virtual ~Variable();
    
    Type* type() const;
    void setType(Type* type);
    
    W_DECLARE_PRIVATE(Variable)
};

W_DECLARE_POINTER(Variable)

}

W_DECLARE_METATYPE(Variable)

#endif // WOBBLE_VARIABLE_H
