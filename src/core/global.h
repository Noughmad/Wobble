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

#include <QtCore/QtGlobal>

#if defined(MAKE_WOBBLE_CORE_LIBRARY)
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
