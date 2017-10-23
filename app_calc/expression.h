#ifndef EXPRESSION_H
#define EXPRESSION_H

#include <QString>

struct Expression
{
    int _id;
    double _a;
    double _b;
    double _result;
    QString _error;

    enum Action {
        Add = 0x1,
        Sub = 0x2,
        Div = 0x3,
        Mul = 0x4,
    };

    Action _action;

    int _time;
};

#endif // EXPRESSION_H
