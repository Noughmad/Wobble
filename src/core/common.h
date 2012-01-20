#ifndef WOBBLE_COMMON_H
#define WOBBLE_COMMON_H

#include "global.h"

namespace Wobble {

class View;
class Type;
    
namespace Common
{
    WOBBLE_EXPORT View* listView();
    WOBBLE_EXPORT View* detailView();
    
    WOBBLE_EXPORT View* listDetailView();
    
    /**
     * Register all Wobble identifier types with the Qt metatype system
     * 
     * @sa qRegisterMetaType
     **/
    WOBBLE_EXPORT void registerTypes();
}

}

#endif // WOBBLE_COMMON_H
