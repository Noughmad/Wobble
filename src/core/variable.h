#ifndef WOBBLE_VARIABLE_H
#define WOBBLE_VARIABLE_H

#include "identifier.h"

#include <QtCore/QSharedPointer>

namespace Wobble {
    
class VariablePrivate;

W_FORWARD(Type)

class WOBBLE_EXPORT Variable : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(TypePtr type READ type WRITE setType)
    
public:
    Variable(const QString& name, TypePtr type, Identifier* space = 0, QObject* parent = 0);
    virtual ~Variable();
    
    TypePtr type() const;
    void setType(TypePtr type);
    
    W_DECLARE_PRIVATE(Variable)
};

W_DECLARE_POINTER(Variable)

}

W_DECLARE_METATYPE(Variable)

#endif // WOBBLE_VARIABLE_H
