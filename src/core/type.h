#ifndef WOBBLE_TYPE_H
#define WOBBLE_TYPE_H

#include "identifier.h"

namespace Wobble {
    
class TypePrivate;

/**
 * @brief An object that represents a variable type
 * 
 * 
 **/
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
    
    /**
     * @brief Names of common built-in types
     * 
     * This enum holds types that are common to (almost) all languages. 
     * 
     * It includes types that are not necessarily present in the languages, 
     * but are supported by widely-used libraries, such as DateTime. 
     * 
     * @sa standardType()
     **/
    enum StandardType
    {
        Character, /**< The character type, usually one byte long */
        String, /**< The basic string type */
        Boolean, /**< The boolean type, holding either true or false */
        Integer, /**< The basic integer type */
        Float, /**< The floating point number type */
        DateTime, /**< A type holding a point in time */
        File, /**< A file */
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
    
    /**
     * @brief Default constructor
     * 
     * Constructs a type with name @p name and namespace @p parent. 
     * 
     * Use this constructor only if your project defines new types that
     * are not classes. For defining classes, use Class directly. 
     * For using common data type, use standardType(). 
     * 
     * @param name name of this type
     * @param parent parent namespace
     **/
    Type(const QString& name, Identifier* parent = 0);
    virtual ~Type();
    
    /**
     * @brief Creates a Type object for a common built-in datatype. 
     * 
     * This is the preferred method for accessing common type. 
     * Different languages have different methods for these type, so
     * it is the Input's task to convert them to StandardType, and
     * the Output's task to give the appropriate name. 
     *
     * @sa StandardType
     * @return Type*
     **/
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
     * @note Some output languages may not differentiate 
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
     * @note Some output languages may not differentiate 
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
