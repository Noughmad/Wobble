#include <QtCore/QtGlobal>

#if defined(MAKE_WOBBLE_LIBRARY)
#  define WOBBLE_EXPORT Q_DECL_EXPORT
#else
#  define WOBBLE_EXPORT Q_DECL_IMPORT
#endif

#define W_USE_NAMESPACE

#ifdef W_USE_NAMESPACE
#       define W_BEGIN_NAMESPACE namespace Wobble {
#       define W_END_NAMESPACE }
#       define W_TYPE(Type) Wobble::Type
#else
#       define W_BEGIN_NAMESPACE
#       define W_END_NAMESPACE
#       define W_TYPE(Type) Type
#endif

#define W_FORWARD(Name) typedef QList<class Name*> Name##List;

#define W_DECLARE_POINTER(Name)                 \
typedef QList<Name*> Name##List;

#define W_DECLARE_METATYPE(Name)                \
Q_DECLARE_METATYPE(Wobble::Name*)           \
Q_DECLARE_METATYPE(Wobble::Name##List)

#define W_BEGIN_CLASS(Name, Super)      \
W_BEGIN_NAMESPACE                       \
class Name##Private;                    \
class Name : public Super {
    
#define W_DECLARE_PRIVATE(Name)                                 \
protected: Name(Name##Private& dd, QObject* parent = 0);        \
private: Q_DECLARE_PRIVATE(Name)

#define W_ACCEPT_VISITOR                                        \
virtual void accept(Visitor* visitor) { visitor->visit(this); }
