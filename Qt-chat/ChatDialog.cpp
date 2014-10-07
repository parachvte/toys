#include "ChatDialog.h"
#include "ui_ChatDialog.h"

#include "ChatClient.h"
#include "ChatServer.h"
#include <QtWidgets>

#include <string>


ChatDialog::ChatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChatDialog)
{
    ui->setupUi(this);

    ui->textView->setFocusPolicy(Qt::NoFocus);
    ui->textView->setReadOnly(true);
    ui->messageEdit->setFocusPolicy(Qt::StrongFocus);
    ui->ipEdit->setFocusPolicy(Qt::WheelFocus);
    ui->ipEdit->setText(QString("localhost"));

    connect(ui->messageEdit, SIGNAL(returnPressed()),
            this, SLOT(returnPressed()));

    // prepare client
    tableFormat.setBorder(0);
    client = new ChatClient();
    server = new ChatServer(); // I'm a separate thread~
    server->start();
}

ChatDialog::~ChatDialog()
{
    delete ui;
    delete client;
    delete server;
}

void ChatDialog::returnPressed()
{
    QString message = ui->messageEdit->text();
    if (message.isEmpty())
        return;

    std::string tmpMessage = message.toUtf8().constData(); // ugly conversion
    const char *cMessage = tmpMessage.c_str();
    client->sendMessage(cMessage);

    appendMessage(QString("Me"), message);

    ui->messageEdit->clear();
}

void ChatDialog::appendMessage(const QString &from, const QString &message)
{
    if (from.isEmpty() || message.isEmpty())
        return;

    QTextCursor cursor(ui->textView->textCursor());
    cursor.movePosition(QTextCursor::End);

    QTextTable *table = cursor.insertTable(1, 2, tableFormat);
    table->cellAt(0, 0).firstCursorPosition().insertText('<' + from + "> ");
    table->cellAt(0, 1).firstCursorPosition().insertText(message);

    QScrollBar *bar = ui->textView->verticalScrollBar();
    bar->setValue(bar->maximum());
}
