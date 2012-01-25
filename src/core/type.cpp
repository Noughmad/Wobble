#include "type.h"
#include "type_p.h"

using namespace Wobble;

typedef QMap<Type::StandardType, Type*> TypeMap;

Q_GLOBAL_STATIC(TypeMap, stdTypes)

TypePrivate::TypePrivate(const QString& name) : IdentifierPrivate(name)
{
    valueType = 0;
    keyType = 0;
    standardType = Type::Custom;
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

void Type::setKeyType(Type* keyType)
{
    Q_D(Type);
    d->keyType = keyType;
}

Type* Type::keyType() const
{
    Q_D(const Type);
    return d->keyType;
}

void Type::setValueType(Type* valueType)
{
    Q_D(Type);
    d->valueType = valueType;
}

Type* Type::valueType() const
{
    Q_D(const Type);
    return d->valueType;
}


Type* Type::findByName(const QString& name)
{
    Type* t = new Type(name);
    t->setObject(false);
    t->setPod(name != "string");
    return t;
}

Type* Type::fromStandardType(Type::StandardType type)
{
    if (!stdTypes()->contains(type))
    {
        Type* t = new Type(standardTypeName(type));
        t->setStandardType(type);
        stdTypes()->insert(type, t);
    }
    return stdTypes()->value(type);
}

QString Type::standardTypeName(Type::StandardType type)
{
    switch (type)
    {
        case Boolean:
            return "bool";
            
        case Integer:
            return "int";
            
        case Character:
            return "char";
            
        case Float:
            return "float";
            
        case String:
            return "string";
            
        case File:
            return "file";
            
        case DateTime:
            return "time";
            
        default:
            qWarning() << "standardTypeName called with a non-standard type" << type;
            return QString();
    }
}

Type::StandardType Type::standardType() const
{
    Q_D(const Type);
    return (StandardType)d->standardType;
}

void Type::setStandardType(Type::StandardType type)
{
    Q_D(Type);
    d->standardType = (int)type;
}



#include "type.moc"
