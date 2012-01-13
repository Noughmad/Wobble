#include "type.h"
#include "type_p.h"

using namespace Wobble;

Type::Type(const QString& name, Wobble::Identifier* space, QObject* parent): Identifier(name, space, parent)
{

}

Type::Type(Wobble::TypePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Type::~Type()
{

}

