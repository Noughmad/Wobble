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
    if (c && c->features() & Class::Persistent && view->queries().size() < 2)
    {
      // TODO: Check for queries
      if (view->queries().isEmpty() || (view->queries().size() == 1 && view->queries().first()->filters().isEmpty()) )
      {
	  writeLine("model = " + view->model()->name());
      }
      else
      {
	  Query* query = view->queries().first();
	  QString queryString = "queryset = " + view->model()->name();
	  foreach (const Query::Filter& filter, query->filters())
	  {
	      if (filter.operation == Query::NotEquals)
	      {
		queryString += QString(".exclude(%1 = %2)").arg(filter.var->name()).arg(filter.value);
	      }
	      else if (filter.operation == Query::Equals)
	      {
		queryString += QString(".filter(%1 = %2)").arg(filter.var->name()).arg(filter.value);
	      }
	      else
	      {
		queryString += QString(".filter(%1__%2 = %3)").arg(filter.var->name()).arg(filterOperation(filter.operation)).arg(filter.value);
	      }
	  }
	  writeLine(queryString);
      }
    }
    else
    {
      writeLine("def get_queryset(self):");
      indent();
      writeLine("#TODO: Get the wanted objects here");
      writeLine("pass");
      unindent();
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
    unindent();
  }
  
  if (view->isLoginRequired())
  {
    indent();
    writeLine("@method_decorator(login_required)");
    writeLine("def dispatch(self, *args, **kwargs):");
    indent();
    writeLine("super(" + view->name() + ", self).dispatch(*args, **kwargs)");
    unindent();
    unindent();
  }

}

QString DjangoWriter::filterOperation(Query::FilterType type)
{
  // A list of all supported filters operations is available at
  // https://docs.djangoproject.com/en/dev/ref/models/querysets/#id4
  switch (type)
  {
    case Query::Equals:
      return "exact";
    case Query::Contains:
      return "contains";
    case Query::IsIn:
      return "in";
    case Query::GreaterThan:
      return "gt";
    case Query::GreaterOrEquals:
      return "gte";
    case Query::LessThan:
      return "lt";
    case Query::LessOrEquals:
      return "lte";
    case Query::StartsWith:
      return "startswith";
    case Query::EndsWith:
      return "endswith";
      
    default:
      return "exact";
  }
  
  return "exact";
}

