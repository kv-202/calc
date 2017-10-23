
#include "calcmodel.h"
#include <algorithm>

CalcModel::CalcModel():
    _request_count(0),
    _last(nullptr),
    _reques(nullptr),
    _reply(nullptr),
    _last_id(1)
{
}

void CalcModel::setRequestCount(int value)
{
    _request_count = value;
    requestCountChanged();
}

void CalcModel::onCalculate(double a, double b, Action action, int sec)
{
    Expression expr = { _last_id, a, b, 0, QString(), static_cast<Expression::Action>(action), sec };
    ++_last_id;

    _history.append(new HistoryItem(expr, true));
    _reques->enqueue(expr);

    historyModelChanged();
    historyItemCountChanged();
    requestCountChanged();
    requestQueueChanged();
}

void CalcModel::onRequestQueueChanged()
{
    requestCountChanged();
}

void CalcModel::onReplyQueueChanged()
{
    Expression expr;
    while (_reply->dequeue(expr))
    {
        auto it = std::find_if(_history.begin(),
                               _history.end(),
                               [&expr] (HistoryItem* a) { return a->data()._id == expr._id; });
        if (it != _history.end())
        {
            (*it)->setResult(expr._result);
            (*it)->setError(expr._error);
            (*it)->setWait(false);
        }
    }
}

QQmlListProperty<HistoryItem> CalcModel::historyModel()
{
    return QQmlListProperty<HistoryItem>(static_cast<QObject*>(this), _history);
}
