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

    connect(server, SIGNAL(messageReceived(QString)),
            this, SLOT(messageReceived(QString)));
}

ChatDialog::~ChatDialog()
{
    delete ui;
    delete client;
    server->terminate();
}

void ChatDialog::returnPressed()
{
    QString message = ui->messageEdit->text();
    if (message.isEmpty())
        return;

    std::string tmpMessage = message.toUtf8().constData(); // ugly conversion
    const char *cMessage = tmpMessage.c_str();
    if (client->sendMessage(cMessage)) {
        appendMessage(QString("Me"), message);
    } else {
        appendMessage(QString("sys"), "message send failed.");
    }

    ui->messageEdit->clear();
}

void ChatDialog::messageReceived(QString message)
{
    appendMessage(QString("Peer"), message);
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

void ChatDialog::on_ipEdit_textChanged(const QString &hostname)
{
    if (client) // client maybe not be instantiated
    {
        std::string sHostname = hostname.toUtf8().constData();
        const char *cHostname = sHostname.c_str();
        client->setServHost(cHostname);
    }
}
