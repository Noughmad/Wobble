/*
    <one line to give the library's name and an idea of what it does.>
    Copyright (C) 2012  Miha Čančula <miha.cancula@gmail.com>

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


#ifndef DJANGOWRITER_H
#define DJANGOWRITER_H

#include <src/utils/codewriter.h>
#include <src/core/query.h>

namespace Wobble {
class Class;
class Function;
class Variable;
class View;
}


class DjangoWriter : public Wobble::CodeWriter
{

public:
    DjangoWriter(QIODevice* device);
    virtual ~DjangoWriter();
    
    void writeLicense(const QString& license);
    void writeModel(Wobble::Class* model);
    void writeFunction(Wobble::Function* function);
    
    void writeView(Wobble::View* view);
    
    QString fieldDeclaration(Wobble::Variable* var);
    QString filterOperation(Wobble::Query::FilterType type);

};

#endif // DJANGOWRITER_H
