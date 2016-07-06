#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringListModel>
#include "Server/Notifier.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void MakeConnections(Notifier *notifier);

private:
    Ui::MainWindow *ui;

    QStringListModel *clientListModel;
    QStringListModel *logListModel;

public slots:
    void changeThreadNumber(int number);
    void changeConnectionNumber(int number);
    void appendToClientList(char *addr);
    void deleteFromClientList(char *addr);
    void appendToLogs(char *log);
};

#endif // MAINWINDOW_H
