#ifndef WOBBLE_VIEW_H
#define WOBBLE_VIEW_H

#include <src/core/class.h>


namespace Wobble {

class ViewPrivate;

/**
 * @brief A represents a single user interface element
 * 
 * A View is a larger reusable user-visible component that displays some data. 
 * Common view include lists (showing multiple items) or single-item details.
 * Their role is similar to that of a Django View or an Android Fragment. 

 * A View is responsible for getting its own data. Most often, a database
 * query is used for this. 
 * 
 * Several views can be combined into a larger view. Wobble provides a set of 
 * default views, including pre-made combinations of list-detail
 * 
 */
class WOBBLE_EXPORT View : public Wobble::Class
{
    Q_OBJECT

public:
    View(const QString& name, Wobble::Identifier* parent = 0);
    virtual ~View();
    
    W_DECLARE_PRIVATE(View)
};

W_DECLARE_POINTER(View)

}

W_DECLARE_METATYPE(View)

#endif // WOBBLE_VIEW_H
