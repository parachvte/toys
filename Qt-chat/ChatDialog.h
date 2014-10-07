#ifndef CHATDIALOG_H
#define CHATDIALOG_H

#include <QDialog>
#include <QtWidgets>

#include "ChatClient.h"
#include "ChatServer.h"

namespace Ui {
class ChatDialog;
}

class ChatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ChatDialog(QWidget *parent = 0);
    ~ChatDialog();

private:
    Ui::ChatDialog *ui;
    QTextTableFormat tableFormat;
    ChatClient *client;
    ChatServer *server;

public slots:
    void appendMessage(const QString &from, const QString &message);

private slots:
    void returnPressed();

};

#endif // CHATDIALOG_H
