#include "debugoutput.h"
#include <QDebug>
#include "src/core/project.h"
#include "src/core/class.h"
#include "src/core/variable.h"
#include "src/core/type.h"

using namespace Wobble;

bool DebugOutput::write(const Project* project, QVariantMap options)
{
    qDebug() << "Project: " << project->name();
    foreach (Wobble::Class* c, project->findChildren<Wobble::Class*>())
    {
        qDebug() << "Class " << c->name();
        if (!c->superclasses().isEmpty())
        {
            qDebug() << " - Superclasses:" << c->superclasses();
        }
        foreach (Wobble::Variable* property, c->findChildren<Wobble::Variable*>())
        {
            qDebug() << " - Property: " << property->type()->name() << " " << property->name();
        }
    }
}

QString DebugOutput::name()
{

}

DebugOutput::DebugOutput(QObject* parent): Output(parent)
{

}

DebugOutput::~DebugOutput()
{

}

Q_EXPORT_PLUGIN2(WobbleDebugOutput, DebugOutput)

#include "debugoutput.moc"
