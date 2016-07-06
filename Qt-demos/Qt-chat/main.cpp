#include "ChatDialog.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ChatDialog chatDialog;
    chatDialog.show();

    int height = QApplication::desktop()->height();
    int width = QApplication::desktop()->width();
    if (height < width) {
        chatDialog.setBaseSize(500, 500);

        // move to center
        chatDialog.move(QApplication::desktop()->screen()->rect().center()
                        - chatDialog.rect().center());
    }

    return app.exec();
}
