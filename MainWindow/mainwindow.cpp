#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "task.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    Task* task = new Task();

    task->setWorkFunc(MainWindow::runThread);

    task->run();

    task->wait();

    delete task;

}

void MainWindow::runThread()
{
    qDebug() << "thread work finished";
}
