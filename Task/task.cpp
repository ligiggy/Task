#include "task.h"
#include "qdebug.h"

Worker::Worker()
    : QObject()
{

}

void Worker::work()
{
    func();


    for(int i = 0; i < 5; i++)
    {
        qDebug() << "working";

        QThread::msleep(1000);
    }


    emit workFinished();
}



/////////////////////////
Task::Task()
    : QObject()
    , m_worker(new Worker)
    , m_thread(new QThread)
{
    //you can use QThread::quit() slot or Task::handleWorkFinish() slot
    //connect(m_worker, &Worker::workFinished, m_thread, &QThread::quit, Qt::DirectConnection);
    connect(m_worker, &Worker::workFinished, this, &Task::handleWorkFinish, Qt::DirectConnection);
    m_worker->moveToThread(m_thread);

    connect(m_thread, &QThread::started, m_worker, &Worker::work);
    connect(m_thread, &QThread::finished, m_thread, &QThread::deleteLater);
}

Task::~Task()
{
    delete m_worker;
}

void Task::handleWorkFinish()
{
    qDebug() << "start to quit";
    m_thread->quit();
}

void Task::run()
{
    m_thread->start();
}

void Task::setWorkFunc(Func func)
{
    m_worker->func = func;
}

void Task::wait()
{
    forever
    {
        qDebug() << m_thread->isRunning();

        if(!m_thread->isRunning())
        {
            break;
        }
        QThread::msleep(1000);
    }
}

bool Task::wait(int ms)
{
    return true;
}

