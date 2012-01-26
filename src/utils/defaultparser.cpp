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

#include "defaultparser.h"
#include "src/core/variable.h"

#include <QStringList>
#include <QDateTime>


using namespace Wobble;

class Wobble::DefaultParserData : public QSharedData
{
public:
    DefaultParserData();
    ~DefaultParserData();
    
    QMap<QString, Type::StandardType> typeNames;
    QStringList trueStrings;
    QStringList falseStrings;
};

DefaultParserData::DefaultParserData()
{
    typeNames.insert("int", Type::Integer);
    typeNames.insert("integer", Type::Integer);
    typeNames.insert("string", Type::String);
    typeNames.insert("bool", Type::Boolean);
    typeNames.insert("boolean", Type::Boolean);
    typeNames.insert("datetime", Type::DateTime);
    typeNames.insert("file", Type::File);
    typeNames.insert("float", Type::Float);
    typeNames.insert("double", Type::Float);

    trueStrings << "true" << "yes" << "1" << "on";
    falseStrings << "false" << "no" << "0" << "off";
}

DefaultParserData::~DefaultParserData()
{

}

DefaultParser::DefaultParser()
: d(new DefaultParserData)
{

}

DefaultParser::DefaultParser(const Wobble::DefaultParser& other)
: d(other.d)
{

}


Wobble::Type* DefaultParser::parseType(const QString& string, Identifier* parent)
{
    QString str = string;
    str.replace(' ', '-');
    if (str.startsWith("list-of-"))
    {
        str.remove(0, 8);
        return Type::list(parseType(str, parent));
    }
    else if (str.startsWith("map-of-"))
    {
        str.remove(0, 7);
        QStringList list = str.split('-', QString::SkipEmptyParts);
        if (list.size() != 2)
        {
            return 0;
        }
        return Type::map(parseType(list[0], parent), parseType(list[1], parent));
    }
    else if (d->typeNames.contains(str))
    {
        return Type::fromStandardType(d->typeNames.value(str));
    }
    return new Type(str, parent);
}

QVariant DefaultParser::parseValue(const QString& string, Type* type, Identifier* parent)
{
    if (type->standardType() == Type::Custom)
    switch (type->standardType())
    {
        case Type::Custom:
        {
            Variable* var;
            if (!(var = parent->findChild<Variable*>(string)))
            {
                var = new Variable(string, type, parent);
            }
            return QVariant::fromValue<Variable*>(var);
        }
        break;

        case Type::Integer:
            return string.toInt();

        case Type::Float:
            return string.toDouble();

        case Type::Boolean:
            if (d->trueStrings.contains(string, Qt::CaseInsensitive))
            {
                return true;
            }
            else if (d->falseStrings.contains(string, Qt::CaseInsensitive))
            {
                return false;
            }
            else
            {
                return QVariant();
            }
            break;

        case Type::DateTime:
            return QDateTime::fromString(string);

        case Type::Character:
            return string.at(0);

        case Type::List:
        case Type::Map:
            qWarning() << "List and map values not supported yet";
            return QVariant();

        case Type::String:
        case Type::File:
            return string;
    }

    return string;
}

