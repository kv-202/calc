#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include "expression.h"
#include <QObject>
#include <QString>

class HistoryItem : public QObject
{
    Q_OBJECT
    Q_PROPERTY(double a READ a NOTIFY aChanged)
    Q_PROPERTY(double b READ b NOTIFY bChanged)
    Q_PROPERTY(int action READ action NOTIFY actionChanged)
    Q_PROPERTY(double result READ result NOTIFY resultChanged)
    Q_PROPERTY(QString error READ error NOTIFY errorChanged)
    Q_PROPERTY(bool wait READ wait NOTIFY waitChanged)

signals:    
    void aChanged();
    void bChanged();
    void actionChanged();
    void resultChanged();
    void errorChanged();
    void waitChanged();
    void testSignal();

public:
    HistoryItem();
    HistoryItem(Expression value, bool wait);

    double a() const { return _data._a; }
    double b() const { return _data._b; }
    int action() const { return _data._action; }
    double result() const { return _data._result; }
    void setResult(double value);
    QString error() const { return _data._error; }
    void setError(const QString &error);
    Expression &data() { return _data; }
    bool wait() const { return _wait; }
    void setWait(bool value);

private:
    Expression _data;
    bool _wait;
};

#endif // HISTORYITEM_H
