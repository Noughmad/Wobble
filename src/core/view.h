#ifndef WOBBLE_VIEW_H
#define WOBBLE_VIEW_H

#include <src/core/class.h>
#include "query.h"


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
class WOBBLE_EXPORT View : public Class
{
    Q_OBJECT
    Q_PROPERTY(bool editable READ isEditable WRITE setEditable)
    Q_PROPERTY(StandardView viewType READ viewType WRITE setViewType)
    Q_PROPERTY(QueryList queries READ queries)
    Q_PROPERTY(QList<View*> subViews READ subViews)

public:
    enum StandardView
    {
        LineView,
        TextView,
        ImageView,
        ClockView,
        ListView,
        Custom
    };
    View(const QString& name, Identifier* parent = 0);
    virtual ~View();
    
    bool isEditable() const;
    void setEditable(bool editable);
    
    StandardView viewType() const;
    void setViewType(StandardView viewType);
    
    QueryList queries() const;
    void addQuery(Query* query);
    
    QList<View*> subViews() const;
    void addSubView(View* view);
    
    W_DECLARE_PRIVATE(View)
};

W_DECLARE_POINTER(View)

}

W_DECLARE_METATYPE(View)

#endif // WOBBLE_VIEW_H
