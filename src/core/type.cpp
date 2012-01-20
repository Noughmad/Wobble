#include "type.h"
#include "type_p.h"

using namespace Wobble;

TypePrivate::TypePrivate(const QString& name) : IdentifierPrivate(name)
{

}

Wobble::TypePrivate::~TypePrivate()
{

}

Type::Type(const QString& name, Wobble::Identifier* parent): Identifier(*new TypePrivate(name), parent)
{
    
}

Type::Type(Wobble::TypePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Type::~Type()
{

}

Type::Source Type::source() const
{
    Q_D(const Type);
    return (Source)d->source;
}

void Type::setSource(Type::Source source)
{
    Q_D(Type);
    d->source = source;
}

bool Type::isPod() const
{
    Q_D(const Type);
    return d->pod;
}

void Type::setPod(bool pod)
{
    Q_D(Type);
    d->pod = pod;
}

bool Type::isObject() const
{
    Q_D(const Type);
    return d->object;
}

void Type::setObject(bool object)
{
    Q_D(Type);
    d->object = object;
}


Type* Type::findByName(const QString& name)
{
    Type* t = new Type(name);
    t->setObject(false);
    t->setPod(name != "string");
    return t;
}

#include "type.moc"
