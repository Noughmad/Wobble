#ifndef WOBBLE_TYPE_H
#define WOBBLE_TYPE_H

#include "identifier.h"

namespace Wobble {
    
class TypePrivate;

class WOBBLE_EXPORT Type : public Identifier
{
    Q_OBJECT
    Q_ENUMS(Source)
    Q_PROPERTY(Source source READ source WRITE setSource)
    
public:
    enum Source
    {
        BuiltIn,
        External,
        Project
    };
    
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
    
    Type(const QString& name, Identifier* parent = 0);
    virtual ~Type();
    
    static Type* standardType(StandardType type);
    static Type* list(Type* values, ListType = DefaultList);
    static Type* map(Type* keys, Type* values, MapType = DefaultMap);
    static Type* findByName(const QString& name);
    
    Source source() const;
    void setSource(Source source);
    
    W_DECLARE_PRIVATE(Type)
};

W_DECLARE_POINTER(Type)

}

W_DECLARE_METATYPE(Type)

#endif // WOBBLE_TYPE_H
