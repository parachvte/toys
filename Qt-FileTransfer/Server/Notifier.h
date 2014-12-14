#ifndef NOTIFIER_H
#define NOTIFIER_H

#include <QObject>

class Notifier : public QObject
{
    Q_OBJECT

public:
    Notifier() {}

    void NotifyThreadNumber(int number);
    void NotifyConnectionNumber(int number);
    void NotifyClientAdded(char *addr);
    void NotifyClientRemoved(char *addr);
    void NotifyLogging(char *log);

signals:
    void ThreadNumberChanged(int number);
    void ConnectionNumberChanged(int number);
    void ClientAdded(char *addr);
    void ClientRemoved(char *addr);
    void Logging(char *log);
};

extern Notifier g_notifier;

#endif // NOTIFIER_H
