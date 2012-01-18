#include "type.h"
#include "type_p.h"

using namespace Wobble;

TypePrivate::TypePrivate(const QString& name, Identifier* space) : IdentifierPrivate(name, space)
{

}

Wobble::TypePrivate::~TypePrivate()
{

}

Type::Type(const QString& name, Wobble::Identifier* space, QObject* parent): Identifier(*new TypePrivate(name, space), parent)
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



#include "type.moc"
