#include "variable.h"
#include "variable_p.h"

using namespace Wobble;

VariablePrivate::VariablePrivate(const QString& name, Type* type, Identifier* space) : IdentifierPrivate(name, space)
{
    this->type = type;
}

Wobble::VariablePrivate::~VariablePrivate()
{

}

Variable::Variable(const QString& name, Type* type, Identifier* space, QObject* parent): Identifier(*new VariablePrivate(name, type, space), parent)
{
    
}

Variable::Variable(VariablePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Variable::~Variable()
{

}

#include "variable.moc"
