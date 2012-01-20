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
    Q_PROPERTY(bool pod READ isPod WRITE setPod)
    Q_PROPERTY(bool object READ isObject WRITE setObject)
    
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
    
    /**
     * @property object
     *
     * Holds whether this type is an object class. 
     * Objects are always passed with pointer. 
     * 
     * @note: Some output languages may not differentiate 
     * between object and non-object types. 
     **/
    bool isObject() const;
    void setObject(bool object);
    
    /**
     * @property pod
     *
     * Holds whether this is a "plain old data" type. 
     * This is true for most core data types like integers, but not for
     * complex data structures like strings or lists. 
     * 
     * POD values are passed by value by default. 
     * 
     * @note: Some output languages may not differentiate 
     * between POD and non-POD types. 
     **/
    bool isPod() const;
    void setPod(bool pod);
    
    W_DECLARE_PRIVATE(Type)
};

W_DECLARE_POINTER(Type)

}

W_DECLARE_METATYPE(Type)

#endif // WOBBLE_TYPE_H
