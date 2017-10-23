
#include "expressioncalculator.h"
#include <QThread>

static QString _NO_DOACTION_FUNCTION = QObject::tr("Wrong library");
static QString _NO_GET_ERROR_FUNCTION = QObject::tr("Wrong library");

ExpressionCalculator::ExpressionCalculator(ThreadSafeQueue<Expression> &reques, ThreadSafeQueue<Expression> &reply):
    _reques(reques),
    _reply(reply),
    _lib("lib_calc"),
    _calulate(nullptr),
    _get_error(nullptr)
{
    if (_lib.load())
    {
        _calulate = reinterpret_cast<double(*)(int, double, double, int&)>(_lib.resolve("DoAction"));
        _get_error = reinterpret_cast<const char* (*)(int)>(_lib.resolve("GetError"));
    }
}

void ExpressionCalculator::onRequestQueueChanged()
{
    Expression expr;
    while (_reques.dequeue(expr))
    {
        requestQueueChanged();

        if (_calulate)
        {
            QThread::sleep(expr._time);

            int error = 0;
            expr._result = _calulate(static_cast<int>(expr._action), expr._a, expr._b, error);

            if (error)
            {
                if (_get_error)
                    expr._error = QString(_get_error(error));
                else
                    expr._error = _NO_GET_ERROR_FUNCTION;
            }
        }
        else
        {
            expr._error = _NO_DOACTION_FUNCTION;
        }

        _reply.enqueue(expr);
        replyQueueChanged();
    }
}
