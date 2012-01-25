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

bool Variable::isConstant() const
{
    Q_D(const Variable);
    return d->constant;
}

void Variable::setConstant(bool constant)
{
    Q_D(Variable);
    d->constant = constant;
}

QVariant Variable::defaultValue() const
{
    Q_D(const Variable);
    return d->defaultValue;
}

void Variable::setDefaultValue(const QVariant& value)
{
    Q_D(Variable);
    d->defaultValue = value;
}

QString Variable::formatValue() const
{
    Q_D(const Variable);
    QVariant val = d->defaultValue;
    if (val.isNull())
    {
        return QString();
    }
    else if (val.type() == QVariant::String)
    {
        return '"' + val.toString() + '"';
    }
    else if (val.canConvert<Variable*>())
    {
        Variable* var = val.value<Variable*>();
        return var->name();
    }
    else
    {
        return val.toString();
    }
}

#include "variable.moc"
