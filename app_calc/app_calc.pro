QT+=widgets qml quick
TARGET=app_calc
TEMPLATE=app
SOURCES=main.cpp \
    calcmodel.cpp \
    historyitem.cpp \
    expressioncalculator.cpp
RESOURCES=app_calc.qrc
HEADERS=calcmodel.h \
    historyitem.h \
    expression.h \
    expressioncalculator.h \
    threadsafequeue.h
