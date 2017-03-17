#ifndef PARAMETERS_HPP
#define PARAMETERS_HPP

class QWidget;

class Parameters
{
public:
    Parameters();
    Parameters(QWidget* view);
    virtual ~Parameters();

    void attach(QWidget* view);
    QWidget* view() const;

    bool isAttached() const;

    virtual void update() = 0;
    virtual void notify() = 0;

    void setRealTime(bool value);
    bool getRealTime() const;

private:
    bool realTime;

private:
    QWidget* v;
};

#endif // PARAMETERS_HPP
