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

#include "hierarchytest.h"

#include "src/core/project.h"
#include "src/core/class.h"
#include "src/core/variable.h"

using namespace Wobble;

void HierarchyTest::initTestCase()
{
  project = new Project();
  project->setName("TestProject");
}

void HierarchyTest::testName()
{
  QCOMPARE(project->name(), QString("TestProject"));
}

void HierarchyTest::testClasses()
{
  ClassList classes;
  classes << new Class("Aligator", project);
  classes << new Class("Beaver", project);
  classes << new Class("Crocodile", project);

  QCOMPARE(project->findMembers<Class*>().size(), 3);
  QCOMPARE(project->findMembers<Class*>().toSet(), classes.toSet());
}

void HierarchyTest::testFinding()
{
  Class* created = new Class("Dragon", project);
  Class* found = project->findOrCreateMember<Class>("Dragon");
  QCOMPARE(found, created);
  QCOMPARE(project->findMembers<Class*>("Dragon").size(), 1);
}

void HierarchyTest::testProperties()
{

  Class* person = new Class("Human", project);
  
  VariableList properties;
  properties << new Variable("name", Type::fromStandardType(Type::String), person);
  properties << new Variable("age", Type::fromStandardType(Type::Integer), person);
  properties << new Variable("birthday", Type::fromStandardType(Type::DateTime), person);

  QCOMPARE(person->properties(), properties);
  QCOMPARE(person->findMembers<Variable*>("age").first(), properties[1]);
  QVERIFY(person->findMembers<Variable*>("nonexistent").isEmpty());
}

void HierarchyTest::testRecursiveness()
{
  QCOMPARE(project->findChildren<Variable*>().size(), 3);
  QCOMPARE(project->findMembers<Variable*>().size(), 0);
}

void HierarchyTest::cleanupTestCase()
{
  delete project;
}

#include "hierarchytest.moc"

QTEST_MAIN(HierarchyTest)