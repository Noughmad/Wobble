#include "Wobble.h"

#include <QTimer>
#include <iostream>

Wobble::Wobble()
{
    QTimer* timer = new QTimer(this);
    connect( timer, SIGNAL(timeout()), SLOT(output()) );
    timer->start( 1000 );
}

Wobble::~Wobble()
{}

void Wobble::output()
{
    std::cout << "Hello World!" << std::endl;
}

#include "Wobble.moc"
