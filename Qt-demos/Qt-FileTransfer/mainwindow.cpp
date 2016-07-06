#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QObject>
#include <QString>
#include <QDebug>
#include <QModelIndex>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // clients
    clientListModel = new QStringListModel();
    QStringList clientList;
    clientListModel->setStringList(clientList);
    ui->ListView_ClientList->setModel(clientListModel);

    // logs
    logListModel = new QStringListModel();
    QStringList logList;
    logListModel->setStringList(logList);
    ui->ListView_Logs->setModel(logListModel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MakeConnections(Notifier *notifier)
{
    QObject::connect(notifier, SIGNAL(ThreadNumberChanged(int)),
            this, SLOT(changeThreadNumber(int)));
    QObject::connect(notifier, SIGNAL(ConnectionNumberChanged(int)),
                     this, SLOT(changeConnectionNumber(int)));
    QObject::connect(notifier, SIGNAL(ClientAdded(char*)),
                     this, SLOT(appendToClientList(char*)));
    QObject::connect(notifier, SIGNAL(ClientRemoved(char*)),
                     this, SLOT(deleteFromClientList(char*)));
    QObject::connect(notifier, SIGNAL(Logging(char*)),
                     this, SLOT(appendToLogs(char*)));
}

void MainWindow::changeThreadNumber(int number)
{
    ui->LCD_ThreadNumber->display(number);
}

void MainWindow::changeConnectionNumber(int number)
{
    ui->LCD_ConnectionNumber->display(number);
}

void MainWindow::appendToClientList(char *addr)
{
    int nRow = clientListModel->rowCount();
    clientListModel->insertRow(nRow);
    QModelIndex index = clientListModel->index(nRow);
    clientListModel->setData(index, addr);
    ui->ListView_ClientList->scrollTo(index);
}

void MainWindow::deleteFromClientList(char *addr)
{
    QString sAddr = QString(addr);
    int nRow = 0;
    foreach (QString s, clientListModel->stringList())
    {
        if (sAddr == s)
        {
            clientListModel->removeRow(nRow);
            break;
        }
        nRow ++;
    }
}

void MainWindow::appendToLogs(char *log)
{
    int nRow = logListModel->rowCount();
    logListModel->insertRow(nRow);
    QModelIndex index = logListModel->index(nRow);
    logListModel->setData(index, log);
    ui->ListView_Logs->scrollTo(index);
    free(log);
}
