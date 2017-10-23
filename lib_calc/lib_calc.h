#ifndef CALCULATE_LIB_H
#define CALCULATE_LIB_H

#include <QtCore/QtGlobal>

#if defined(CALCULATE_LIB)
#  define CALCULATE_LIB_DLLSPEC Q_DECL_EXPORT
#else
#  define CALCULATE_LIB_DLLSPEC Q_DECL_IMPORT
#endif

#define SUCCESS 0
#define DIV_BY_ZERO 1
#define WRONG_OPERATION 2

#define ADD 1
#define SUB 2
#define DIV 3
#define MUL 4

extern "C" CALCULATE_LIB_DLLSPEC double DoAction(int TypeWork, double OperandA, double OperandB, int& ErrorCode);
extern "C" CALCULATE_LIB_DLLSPEC const char *GetError(int error);

#endif
