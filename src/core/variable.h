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
    Q_PROPERTY(bool constant READ isConstant WRITE setConstant)
    
public:
    Variable(const QString& name, Type* type, Identifier* parent = 0);
    virtual ~Variable();
    
    /**
     * @property type
     * 
     * The type of this variable. 
     *
     * Not all languages require a variable to have a predetermined type, 
     * but Wobble does. 
     * 
     **/
    Type* type() const;
    void setType(Type* type);
    
    /**
     * @property constant
     *
     * Holds whether this variable is constant, i.e. it cannot be changed
     * after it is first set. 
     * 
     * If a class member is constant, no setter will be provided. 
     **/
    bool isConstant() const;
    void setConstant(bool constant);
    
    W_DECLARE_PRIVATE(Variable)
};

W_DECLARE_POINTER(Variable)

}

W_DECLARE_METATYPE(Variable)

#endif // WOBBLE_VARIABLE_H
