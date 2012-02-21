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


#include "djangowriter.h"
#include <src/core/function.h>
#include <src/core/variable.h>
#include <QStringList>
#include <src/core/class.h>
#include <src/core/view.h>

using namespace Wobble;

DjangoWriter::DjangoWriter(QIODevice* device) : CodeWriter(device)
{

}

DjangoWriter::~DjangoWriter()
{

}

void DjangoWriter::writeLicense(const QString& license)
{
  writeLine("'''");
  indent();
  foreach (const QString& line, license.split(' '))
  {
    writeLine(line);
  }
  unindent();
  writeLine("'''");
}

void DjangoWriter::writeFunction(Function* function)
{
  QString declaration = "def " + function->name() + "(self,";
  QStringList args;
  if (function->parent() && qobject_cast<Class*>(function->parent()))
  {
    args << "self";
  }
  foreach (Variable* var, function->arguments())
  {
    args << var->name();
  }
  declaration += args.join(",") + ')';
  writeLine(declaration);
  addBlock(QStringList() << "# TODO: Implement" << "pass");
}

void DjangoWriter::writeModel(Class* model)
{
  writeLine("");
  writeLine("class " + model->name() + ':');
  indent();
  foreach (Variable* var, model->properties())
  {
      writeLine(var->name() + " = " + fieldDeclaration(var) );
  }
  foreach (Function* fun, model->methods())
  {
      writeFunction(fun);
  }
  unindent();
}

QString DjangoWriter::fieldDeclaration(Wobble::Variable* var)
{
    QString line;

    QString type = var->type()->name();
    if (type == Type::standardTypeName(Type::Integer))
    {
        line = "IntegerField(";
    }
    else if (type == Type::standardTypeName(Type::Boolean))
    {
        line = "BooleanField(";
    }
    else if (type == Type::standardTypeName(Type::Float))
    {
        line = "FloatField(";
    }
    else if (type == Type::standardTypeName(Type::String))
    {
        line = "TextField(";
    }
    else if (type == Type::standardTypeName(Type::DateTime))
    {
        line = "DateTimeField(";
    }
    // TODO: Check for other types
    else if (type == var->space()->name())
    {
        line = "ForeignKey('self', blank=True, null=True,";
    }
    else
    {
        line = "ForeignKey(" + type;
    }

    if (var->defaultValue().isValid())
    {
        line += "default=";
        line += var->formatValue();
        line += ", ";
    }

    if (line.endsWith(", "))
    {
        line.chop(2);
    }

    return line + ')';
}

void DjangoWriter::writeView(View* view)
{
  if (view->model() && view->model()->isObject())
  {
    writeLine("class " + view->name() + "(DetailView):");
    indent();
    Class* c = qobject_cast<Class*>(view->model());
    if (c && c->features() & Class::Persistent)
    {
      // TODO: Check for queries
      writeLine("model = " + view->model()->name());
    }
    else
    {
      writeLine("# TODO: Get the object");
      writeLine("pass");
    }
    unindent();
  }
  else if (view->model() && view->model()->standardType() == Type::List)
  {
    writeLine("class " + view->name() + "(ListView):");
    indent();
    Class* c = qobject_cast<Class*>(view->model()->valueType());
    if (c && c->features() & Class::Persistent)
    {
      // TODO: Check for queries
      writeLine("model = " + view->model()->valueType()->name());
    }
    else
    {
      writeLine("# TODO: Get the objects");
      writeLine("pass");
    }
    unindent();
  }
  else
  {
    writeLine("class " + view->name() + "(View):");
    indent();
    writeLine("# TODO: Implement the view");
    writeLine("def get(self):");
    addBlock(QStringList() << "pass");
  }
}
