
#include "historyitem.h"

HistoryItem::HistoryItem():
    _data( {0, 0, 0, 0, QString(), Expression::Add, 0 } ),
    _wait(false)
{
}

HistoryItem::HistoryItem(Expression value, bool wait):
    _data(value),
    _wait(wait)
{
}

void HistoryItem::setResult(double value)
{
    _data._result = value;
    resultChanged();
}

void HistoryItem::setError(const QString &error)
{
    _data._error = error;
    errorChanged();
}

void HistoryItem::setWait(bool value)
{
    _wait = value;
    waitChanged();
}
