#include "resource.h"
#include "resource_p.h"

using namespace Wobble;

ResourcePrivate::ResourcePrivate(const QString& name) : IdentifierPrivate(name)
{
}

Wobble::ResourcePrivate::~ResourcePrivate()
{

}

Resource::Resource(const QString& name, Wobble::Identifier* parent): Identifier(*new ResourcePrivate(name), parent)
{
    
}

Resource::Resource(Wobble::ResourcePrivate& dd, QObject* parent): Identifier(dd, parent)
{

}

Resource::~Resource()
{

}

QString Resource::filename() const
{
    Q_D(const Resource);
    return d->filename;
}

void Resource::setFilename(const QString filename)
{
    Q_D(Resource);
    d->filename = filename;
}

#include "resource.moc"
