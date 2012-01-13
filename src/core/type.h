#ifndef WOBBLE_TYPE_H
#define WOBBLE_TYPE_H

#include "identifier.h"

namespace Wobble {
    
class TypePrivate;
class Class;

class Type : public Identifier
{

public:
    enum StandardType
    {
        Character,
        String,
        Boolean,
        Integer,
        Float
    };
    
    enum ListType
    {
        DefaultList,
        Array,
        LinkedList
    };
    
    enum MapType
    {
        DefaultMap,
        SingleMap,
        MultiMap,
        SingleHash,
        MultiHash
    };
    
    Type(const QString& name, Identifier* space = 0, QObject* parent = 0);
    Type(Class* cls);
    
    static Type* standardType(StandardType type);
    static Type* list(Type* values, ListType = DefaultList);
    static Type* map(Type* keys, Type* values, MapType = DefaultMap);

protected:
    Type(TypePrivate& dd, QObject* parent = 0);

public:
    virtual ~Type();
};

}

#endif // WOBBLE_TYPE_H
