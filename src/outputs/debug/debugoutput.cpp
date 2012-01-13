#include "debugoutput.h"
#include <QDebug>
#include "src/core/project.h"
#include "src/core/class.h"

bool DebugOutput::write(Wobble::Project* project, QVariantMap options)
{
    qDebug() << "Project: " << project->name();
    foreach (Wobble::Identifier* id, project->members())
    {
        qDebug() << id->metaObject()->className() << id->fullName("/");
        if (Wobble::Class* c = qobject_cast<Wobble::Class*>(id))
        {
            if (!c->superclasses().isEmpty())
                qDebug() << " - Superclasses:" << c->superclasses();
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
