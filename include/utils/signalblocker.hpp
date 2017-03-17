#ifndef SIGNALBLOCKER_HPP
#define SIGNALBLOCKER_HPP

class QObject;

class SignalBlocker
{
public:
    SignalBlocker();
    SignalBlocker(QObject* object);
    ~SignalBlocker();

    void block();
    void unblock();

    bool hasObject() const;

    void setObject(QObject* o);

private:
    QObject* object;
};

#endif // SIGNALBLOCKER_H
