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


#ifndef WOBBLE_CODEWRITER_H
#define WOBBLE_CODEWRITER_H

#include <QtCore/QObject>

class QStringList;
class QIODevice;

namespace Wobble {

class CodeWriterPrivate;
class CodeWriter
{

public:
    CodeWriter(QIODevice* device);
    virtual ~CodeWriter();
    
    int indentation() const;
    void setIndentation(int indentation);
    void indent();
    void unindent();
    
    void setIndentationWidth(int width);
    int indentationWidth() const;
    
    void writeLine(const QString& line);
    void addBlock(const QStringList& lines);    
    
private:
    CodeWriterPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(CodeWriter)
};

}

#endif // WOBBLE_CODEWRITER_H
