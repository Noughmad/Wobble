#ifndef DEBUGOUTPUT_H
#define DEBUGOUTPUT_H

#include "src/core/output.h"

#include <QtPlugin>

class DebugOutput : public Wobble::Output
{
    Q_OBJECT
    Q_INTERFACES(Wobble::Output)
    
public:
    virtual bool write(const Wobble::Project* project, QVariantMap options);
    virtual QString name();
    explicit DebugOutput(QObject* parent = 0);
    virtual ~DebugOutput();
};

#endif // DEBUGOUTPUT_H
