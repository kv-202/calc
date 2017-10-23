
#include "lib_calc.h"
#include <iostream>

static const char* _DIV_BY_ZERO = "Divide by zero";
static const char* _WRONG_OPERATION = "Wrong operation";

double DoAction(int typeWork, double operandA, double operandB, int& errorCode)
{
    errorCode = (SUCCESS);

    switch (typeWork)
    {
    case (ADD):
        return operandA + operandB;
    case (SUB):
        return operandA - operandB;
    case (DIV):
        if (operandB == 0)
        {
            errorCode = (DIV_BY_ZERO);
            return 0;
        }
        return operandA / operandB;
    case (MUL):
        return operandA * operandB;
    default:
        errorCode = (WRONG_OPERATION);
    }
    return 0;
}

const char *GetError(int error)
{
    switch (error)
    {
    case (DIV_BY_ZERO):
        return _DIV_BY_ZERO;
    case (WRONG_OPERATION):
        return _WRONG_OPERATION;
    }
    return 0;
}
