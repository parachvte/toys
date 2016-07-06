#include "Notifier.h"
#include <windows.h>
#include <QTimer>

Notifier g_notifier;


void Notifier::NotifyThreadNumber(int number)
{
    emit ThreadNumberChanged(number);
}

void Notifier::NotifyConnectionNumber(int number)
{
    emit ConnectionNumberChanged(number);
}

void Notifier::NotifyClientAdded(char *addr)
{
    emit ClientAdded(addr);
}

void Notifier::NotifyClientRemoved(char *addr)
{
    emit ClientRemoved(addr);
}

void Notifier::NotifyLogging(char *log)
{
    emit Logging(log);
}
