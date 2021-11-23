#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QThread>

typedef void (*Func)();

class Worker : public QObject
{
    Q_OBJECT
public:
    Worker();

public:
    void work();

public:
    Func func;

signals:
    void workFinished();

};


class Task : public QObject
{
    Q_OBJECT
public:
    Task();
    ~Task();

private:
    void handleWorkFinish();

public:
    void run();

    void setWorkFunc(Func func);

    void wait();
    bool wait(int ms);

private:
    Worker* m_worker;

    QThread* m_thread;

};

#endif // TASK_H
