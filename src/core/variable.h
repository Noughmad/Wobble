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
    Q_PROPERTY(QVariant defaultValue READ defaultValue WRITE setDefaultValue)
    
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

    /**
     * @property defaultValue
     *
     * Holds the defualt value of this variable,
     * or a null variant if no default should be set
     *
     * It can be a constant value (1, "Dog", 3.2) or
     * a pointer to another variable
     * 
     **/
    QVariant defaultValue() const;
    void setDefaultValue(const QVariant& value);

    /**
     * @brief Returns the default value, formatted for direct use in source files
     *
     * 
     *
     * @return QString
     **/
    QString formatValue() const;

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Variable)
};

W_DECLARE_POINTER(Variable)

}

W_DECLARE_METATYPE(Variable)

#endif // WOBBLE_VARIABLE_H
