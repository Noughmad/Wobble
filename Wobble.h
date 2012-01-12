#ifndef Wobble_H
#define Wobble_H

#include <QtCore/QObject>

class Wobble : public QObject
{
Q_OBJECT
public:
    Wobble();
    virtual ~Wobble();
private slots:
    void output();
};

#endif // Wobble_H
