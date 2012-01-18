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

Type* Type::findByName(const QString& name)
{
    return new Type(name);
}

#include "type.moc"
