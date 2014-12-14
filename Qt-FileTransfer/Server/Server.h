#ifndef SERVERTHREAD_H
#define SERVERTHREAD_H

#include <QThread>
#include "mainwindow.h"


class Server : public QThread
{
    MainWindow *ui;

public:
    Server();

protected:
    void run();
};

#endif // SERVERTHREAD_H
