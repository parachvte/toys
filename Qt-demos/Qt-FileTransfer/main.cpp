#include <QApplication>
#include "mainwindow.h"
#include "Server/Server.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    Server *server;

    // Main window
    mainWindow.show();

    // Starting server
    server = new Server();
    server->start();

    mainWindow.MakeConnections(&g_notifier);

    return app.exec();
}
