/*
    This file is part of Wobble, a code generation framework
    Copyright (C) 2012  Miha Čančula miha@noughmad.eu

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Lesser General Public
    License as published by the Free Software Foundation; either
    version 2.1 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this library; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef WOBBLE_VIEW_H
#define WOBBLE_VIEW_H

#include "identifier.h"
#include "query.h"


namespace Wobble {

class ViewPrivate;
W_FORWARD(View)

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
class WOBBLE_EXPORT View : public Identifier
{
    Q_OBJECT
    Q_PROPERTY(bool editable READ isEditable WRITE setEditable)
    Q_PROPERTY(QueryList queries READ queries)
    Q_PROPERTY(ViewList subViews READ subViews)
    Q_PROPERTY(View* listItem READ listItem WRITE setListItem)
    Q_PROPERTY(Type* model READ model WRITE setModel)
    Q_PROPERTY(bool loginRequired READ isLoginRequired WRITE setLoginRequired)

public:
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
    ViewList subViews() const;
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

    /**
     * @property model
     *
     * If this view has a direct mapping to a single class type,
     * this class type is saved here. Otherwise, this property is 0.
     *
     * If model is a list type, this view will show a list as well. 
     *
     **/
    Type* model() const;
    void setModel(Type* model);
    
    /**
     * @property loginRequired
     * 
     * Holds whether this view is only available to logged-in users. 
     * 
     * This property only makes sense in multi-user environments, such as web applications. 
     **/
    bool isLoginRequired() const;
    void setLoginRequired(bool loginRequired);

    /**
     * @brief Creates a view with a direct mapping to a type.
     *
     * If @p type is a basic type, a single widget will be show.
     * If it is a class with properties, a widget will be created for each property.
     * If @p type is a list type, the returned view will show a list as well.
     *
     * @sa model()
     *
     * @param type The type that should be displayed or edited by this view.  
     * @return :View*
     **/
    static View* fromType(Type* type);

    W_ACCEPT_VISITOR
    W_DECLARE_PRIVATE(View)
};

W_DECLARE_POINTER(View)

}

W_DECLARE_METATYPE(View)

#endif // WOBBLE_VIEW_H
