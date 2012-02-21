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


#include "codewriter.h"

#include <QtCore/QIODevice>
#include <QtCore/QTextStream>
#include <QtCore/QStringList>

using namespace Wobble;

class Wobble::CodeWriterPrivate
{
public:
  int indentation;
  int width;
  QTextStream stream;
};

CodeWriter::CodeWriter(QIODevice* device) : d_ptr(new CodeWriterPrivate)
{
  Q_D(CodeWriter);
  d->width = 4;
  d->indentation = 0;
  setDevice(device);
}


CodeWriter::~CodeWriter()
{
  delete d_ptr;
}

void CodeWriter::setDevice(QIODevice* device)
{
  Q_D(CodeWriter);
  d->stream.setDevice(device);
}


int CodeWriter::indentation() const
{
  Q_D(const CodeWriter);
  return d->indentation;
}

void CodeWriter::setIndentation(int indentation)
{
  Q_D(CodeWriter);
  d->indentation = indentation;
}


void CodeWriter::indent()
{
  Q_D(CodeWriter);
  d->indentation++;
}

void CodeWriter::unindent()
{
  Q_D(CodeWriter);
  Q_ASSERT(d->indentation > 0);
  d->indentation--;
}

int CodeWriter::indentationWidth() const
{
  Q_D(const CodeWriter);
  return d->width;
}

void CodeWriter::setIndentationWidth(int width)
{
  Q_D(CodeWriter);
  d->width = width;
}

void CodeWriter::writeLine(const QString& line)
{
  Q_D(CodeWriter);
  QString indent;
  indent.fill(' ', d->width * d->indentation);
  d->stream << indent << line << endl;
}

void CodeWriter::newLine()
{
  Q_D(CodeWriter);
  d->stream << endl;
}

void CodeWriter::addBlock(const QStringList& lines)
{
  indent();
  foreach (const QString& line, lines)
  {
    writeLine(line);
  }
  unindent();
}

