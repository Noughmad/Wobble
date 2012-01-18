#include "variable.h"
#include "variable_p.h"

using namespace Wobble;

VariablePrivate::VariablePrivate(const QString& name, TypePtr type, Identifier* space) : IdentifierPrivate(name, space)
{
    this->type = type;
}

Wobble::VariablePrivate::~VariablePrivate()
{

}

Variable::Variable(const QString& name, TypePtr type, Identifier* space, QObject* parent): Identifier(*new VariablePrivate(name, type, space), parent)
{
    
}

Variable::Variable(VariablePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Variable::~Variable()
{

}

void Variable::setType(TypePtr type)
{
    Q_D(Variable);
    d->type = type;
}

TypePtr Variable::type() const
{
    Q_D(const Variable);
    return d->type;
}


#include "variable.moc"
