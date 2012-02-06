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

#include "yamltest.h"
#include <src/core/project.h>
#include <src/core/input.h>
#include <src/core/plugins.h>
#include <src/core/resource.h>
#include <src/core/class.h>

using namespace Wobble;

void YamlTest::initTestCase()
{
    project = new Project();
    Input* in = Plugins::loadInput("YAML");
    QVariantMap options;
    options["filename"] = "/home/miha/Programiranje/Wobble/test/zoo.yaml";
    m_parsed = in->read(project, options);
}

void YamlTest::testParsing()
{
  QVERIFY(m_parsed);
}

void YamlTest::testOptions()
{
  QCOMPARE(project->hasNotifier(), false);
  QVERIFY(project->icon());  
  QCOMPARE(project->icon()->filename(), QString("zoo.png"));
}

void YamlTest::testClasses()
{
  QCOMPARE(project->findMembers<Class*>().size(), 4);
}

void YamlTest::testInheritance()
{
  QCOMPARE(project->findMembers<Class*>("Bird").first()->superclasses().size(), 1);
  QCOMPARE(project->findMembers<Class*>("Mouse").first()->superclasses().size(), 1);
  QCOMPARE(project->findMembers<Class*>("Mouse").first()->superclasses().first()->name(), QString("Mammal"));
}

void YamlTest::cleanupTestCase()
{
  delete project;
}


#include "yamltest.moc"

QTEST_MAIN(YamlTest)