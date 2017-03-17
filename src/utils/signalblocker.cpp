#include "utils/signalblocker.hpp"

#include <QObject>

SignalBlocker::SignalBlocker() : object(nullptr) {}

SignalBlocker::SignalBlocker(QObject* object) : object(object)
{
    block();
}

SignalBlocker::~SignalBlocker()
{
    if(object)
    {
        object->blockSignals(false);
    }
}

void SignalBlocker::block()
{
    if(object)
    {
        object->blockSignals(true);
    }
}

void SignalBlocker::unblock()
{
    if(object)
    {
        object->blockSignals(false);
    }
}

bool SignalBlocker::hasObject() const
{
    return (object != nullptr);
}

void SignalBlocker::setObject(QObject* o)
{
    object = o;
}
