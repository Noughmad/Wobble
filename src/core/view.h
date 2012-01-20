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
    Q_PROPERTY(View* listItem READ listItem WRITE setListItem)

public:
    /**
     * Enumeration of standard view types
     **/
    enum StandardView
    {
        LineView, /**< A single line of text */
        TextView, /**< A multi-line text view */
        ImageView, /**< A view showing a sigle image */
        ClockView, /**< A clock, either analog or digital */
        ListView, /**< A list view */
        Custom /**< None of the above, to be defined in per-platform application code */
    };
    View(const QString& name, Identifier* parent = 0);
    virtual ~View();
    
    /**
     * @property editable
     * 
     * Holds whether the contents of this View can be 
     * edited by the user
     **/
    bool isEditable() const;
    void setEditable(bool editable);
    
    /**
     * @property viewType
     *
     * The type of this view
     * @sa StandardView
     * 
     **/
    StandardView viewType() const;
    void setViewType(StandardView viewType);
    
    /**
     * @property queries
     * 
     * A list of queries that return all the data needed by this view. 
     * 
     * List views should have only one query that fetches several items. 
     *
     **/
    QueryList queries() const;
    void addQuery(Query* query);
    
    /**
     * @property subViews
     * 
     * If this is a composite view, this property lists all the views 
     * it contains. 
     *
     **/
    QList<View*> subViews() const;
    void addSubView(View* view);
    
    /**
     * @property listItem
     *
     * If this is a list view, this property holds a view that is to be
     * displayed for every item in the list. It is only used if 
     * viewType() is set to ListView. 
     * 
     * @sa viewType(), StandardView
     **/
    View* listItem() const;
    void setListItem(View* listItem);
    
    W_DECLARE_PRIVATE(View)
};

W_DECLARE_POINTER(View)

}

W_DECLARE_METATYPE(View)

#endif // WOBBLE_VIEW_H
