#ifndef CALCMODEL_H
#define CALCMODEL_H

#include "expression.h"
#include "threadsafequeue.h"
#include "historyitem.h"
#include <QObject>
#include <QStringListModel>
#include <QSharedPointer>
#include <QQmlListProperty>

class CalcModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int requestCount READ requestCount NOTIFY requestCountChanged)
    Q_PROPERTY(QQmlListProperty<HistoryItem> historyModel READ historyModel NOTIFY historyModelChanged)

public:
    enum Action {
        Add = 0x1,
        Sub = 0x2,
        Div = 0x3,
        Mul = 0x4,
    };
    Q_ENUMS(Action)

signals:
    void requestCountChanged();
    void historyModelChanged();
    void historyItemCountChanged();   
    void requestQueueChanged();

public slots:
    void onCalculate(double a, double b, Action action, int sec);
    void onRequestQueueChanged();
    void onReplyQueueChanged();

public:
    CalcModel();

    void setRequestQueue(ThreadSafeQueue<Expression> *value) { _reques = value; }
    void setReplyQueue(ThreadSafeQueue<Expression> *value) { _reply = value; }

    int requestCount() const { return _reques->size(); }
    void setRequestCount(int value);

    QQmlListProperty<HistoryItem> historyModel();

private:
    int _request_count;
    QList<HistoryItem*> _history;
    HistoryItem *_last;
    ThreadSafeQueue<Expression> *_reques;
    ThreadSafeQueue<Expression> *_reply;
    int _last_id;
};

#endif // CALCMODEL_H
