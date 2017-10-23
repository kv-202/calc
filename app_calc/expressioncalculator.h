#ifndef EXPRESSIONCALCULATOR_H
#define EXPRESSIONCALCULATOR_H

#include "expression.h"
#include "threadsafequeue.h"
#include <QObject>
#include <QLibrary>
#include <functional>

class ExpressionCalculator : public QObject
{
    Q_OBJECT
signals:
    void replyQueueChanged();
    void requestQueueChanged();

public slots:
    void onRequestQueueChanged();

public:
    ExpressionCalculator(ThreadSafeQueue<Expression> &reques, ThreadSafeQueue<Expression> &reply);

private:
    ThreadSafeQueue<Expression> &_reques;
    ThreadSafeQueue<Expression> &_reply;
    QLibrary _lib;
    std::function<double(int, double, double, int&)> _calulate;
    std::function<const char*(int)> _get_error;
};

#endif // EXPRESSIONCALCULATOR_H
