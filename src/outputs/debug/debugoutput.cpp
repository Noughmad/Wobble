#include "debugoutput.h"
#include <QDebug>
#include "src/core/project.h"
#include "src/core/class.h"
#include "src/core/variable.h"
#include "src/core/type.h"
#include "src/core/query.h"
#include "src/core/view.h"

using namespace Wobble;

bool DebugOutput::write(const Project* project, QVariantMap options)
{
    qDebug() << "Project: " << project->name();
    foreach (Wobble::Class* c, project->findChildren<Wobble::Class*>())
    {
        qDebug() << "Class" << c->name();
        if (!c->superclasses().isEmpty())
        {
            qDebug() << " - Superclasses:" << c->superclasses();
        }
        foreach (Wobble::Variable* property, c->findChildren<Wobble::Variable*>())
        {
            qDebug() << " - Property:" << property->type()->name() << property->name();
        }
    }
    foreach (Wobble::View* v, project->findChildren<Wobble::View*>())
    {
        qDebug() << "View" << v->name();
        qDebug() << " - Editable" << v->isEditable();
        if (v->viewType() == View::ListView)
        {
            qDebug() << " - List item" << v->listItem()->name();
        }
        foreach (Wobble::Query* q, v->queries())
        {
            qDebug() << " - Query" << q->name();
            qDebug() << "   - Type" << q->type()->name();
            foreach (const Wobble::Query::Filter& f, q->filters())
            {
                qDebug() << "   - Filter:" << f.var->name() << f.value;
            }
        }
    }
    
    return true;
}

QString DebugOutput::name()
{
    return "Debug";
}

DebugOutput::DebugOutput(QObject* parent): Output(parent)
{

}

DebugOutput::~DebugOutput()
{

}

Q_EXPORT_PLUGIN2(WobbleDebugOutput, DebugOutput)

#include "debugoutput.moc"
