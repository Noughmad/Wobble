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

#include "type.moc"
