#ifndef WOBBLE_RESOURCE_H
#define WOBBLE_RESOURCE_H

#include "identifier.h"

namespace Wobble {
    
class ResourcePrivate;

/**
 * @brief Represents a resource loaded by the program
 *
 * Most common types of resources are images.
 *
 * In Wobble, a Resource is an Identifier, so it has a name and a place in
 * the hierarchy. These two properties should be used when referring to this resource. 
 * 
 **/
class WOBBLE_EXPORT Resource : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(QString filename READ filename WRITE setFilename)
    
public:
    
    /**
     * @brief Default constructor
     * 
     * Constructs a resource with name @p name and namespace @p parent. 
     * 
     * @param name name of this resource
     * @param parent parent namespace
     **/
    Resource(const QString& name, Identifier* parent = 0);
    virtual ~Resource();
    
    /**
     * @property filename
     *
     * The file from which this resource is loaded. 
     **/
    QString filename() const;
    void setFilename(const QString filename);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(Resource)
};

W_DECLARE_POINTER(Resource)

}

W_DECLARE_METATYPE(Resource)

#endif // WOBBLE_RESOURCE_H
