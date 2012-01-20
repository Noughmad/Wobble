#ifndef WOBBLE_COMMON_H
#define WOBBLE_COMMON_H

#include "global.h"
#include "type.h"

namespace Wobble {

class View;
class Type;
class Class;
class Variable;
    
namespace Common
{
    WOBBLE_EXPORT View* listView();
    WOBBLE_EXPORT View* detailView();
    
    WOBBLE_EXPORT View* listDetailView();
    
    WOBBLE_EXPORT View* standardTypeView(Type::StandardType type, bool editable = false);
    WOBBLE_EXPORT View* variableView(Variable* var, bool editable = false);
    WOBBLE_EXPORT View* classView(Class* c, bool editable = false);
    
    /**
     * Register all Wobble identifier types with the Qt metatype system
     * 
     * @sa qRegisterMetaType
     **/
    WOBBLE_EXPORT void registerTypes();
}

}

#endif // WOBBLE_COMMON_H
