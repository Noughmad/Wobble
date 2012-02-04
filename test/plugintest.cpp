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

#include "plugintest.h"

#include "src/core/plugins.h"
#include "src/core/input.h"
#include "src/core/output.h"

void PluginTest::initTestCase()
{

}

void PluginTest::testInputs()
{
  QList<QByteArray> expected;
  expected << "YAML";
  QList<QByteArray> received = Wobble::Plugins::availableInputs();
  QCOMPARE(received.size(), expected.size());
  QCOMPARE(received.toSet(), expected.toSet());
}

void PluginTest::testOutputs()
{
  QList<QByteArray> expected;
  expected << "C++" << "Debug" << "Django";
  QList<QByteArray> received = Wobble::Plugins::availableOutputs();
  QCOMPARE(received.size(), expected.size());
  QCOMPARE(received.toSet(), expected.toSet());
}

void PluginTest::testLoading()
{
  QVERIFY(Wobble::Plugins::loadInput("YAML"));
  QVERIFY(Wobble::Plugins::loadOutput("C++"));
  QVERIFY(Wobble::Plugins::loadOutput("Debug"));
  QVERIFY(Wobble::Plugins::loadOutput("Django"));
}

void PluginTest::testError()
{
  QCOMPARE(Wobble::Plugins::loadInput("NonexistentInput"), (Wobble::Input*)0);
  QCOMPARE(Wobble::Plugins::loadOutput("NonexistentOutput"), (Wobble::Output*)0);
}

void PluginTest::cleanupTestCase()
{

}

#include "plugintest.moc"

QTEST_MAIN(PluginTest)