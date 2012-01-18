#include "variable.h"
#include "variable_p.h"

using namespace Wobble;

VariablePrivate::VariablePrivate(const QString& name, Type* type) : IdentifierPrivate(name)
{
    this->type = type;
}

Wobble::VariablePrivate::~VariablePrivate()
{

}

Variable::Variable(const QString& name, Type* type, Identifier* parent): Identifier(*new VariablePrivate(name, type), parent)
{
    
}

Variable::Variable(VariablePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Variable::~Variable()
{

}

void Variable::setType(Type* type)
{
    Q_D(Variable);
    d->type = type;
}

Type* Variable::type() const
{
    Q_D(const Variable);
    return d->type;
}


#include "variable.moc"
