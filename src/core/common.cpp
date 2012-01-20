#include "common.h"

#include "identifier.h"
#include "type.h"
#include "class.h"
#include "variable.h"

#include <QMetaType>



using namespace Wobble;

View* Common::detailView()
{
    return 0;
}

View* Common::listDetailView()
{
    return 0;
}

View* Common::listView()
{
    return 0;
}

void Common::registerTypes()
{
    qRegisterMetaType<Identifier*>("Identifier*");
    qRegisterMetaType<Type*>("Type*");
}
