
#include "expressioncalculator.h"
#include "threadsafequeue.h"
#include "expression.h"
#include "calcmodel.h"
#include "historyitem.h"
#include <QtDebug>
#include <QApplication>
#include <QQmlEngine>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQuickView>
#include <QThread>
#include <QSettings>
#include <QVariant>

int main(int argc, char **argv)
{  
    QApplication app(argc, argv);
    QSettings sett("app_calc_cfg", QSettings::IniFormat);

    ThreadSafeQueue<Expression> reques;
    ThreadSafeQueue<Expression> reply;

    ExpressionCalculator calkWorker(reques, reply);
    QThread thread;
    calkWorker.moveToThread(&thread);
    thread.start();

    qmlRegisterType<HistoryItem>("calc", 1, 0, "HistoryItem");
    qmlRegisterType<CalcModel>("calc", 1, 0, "CalcModel");

    QQmlEngine engine;
    QQmlContext context(engine.rootContext());

    CalcModel calcModel;
    calcModel.setRequestQueue(&reques);
    calcModel.setReplyQueue(&reply);

    QObject::connect(&calkWorker,
                     &ExpressionCalculator::replyQueueChanged,
                     &calcModel,
                     &CalcModel::onReplyQueueChanged);
    QObject::connect(&calkWorker,
                     &ExpressionCalculator::requestQueueChanged,
                     &calcModel,
                     &CalcModel::onRequestQueueChanged);
    QObject::connect(&calcModel,
                     &CalcModel::requestQueueChanged,
                     &calkWorker,
                     &ExpressionCalculator::onRequestQueueChanged);

    context.setContextProperty(QString("calcModel"), &calcModel);

    QQmlComponent component(&engine, ":/main.qml");
    QQuickWindow *topLevel = qobject_cast<QQuickWindow*>(component.create(&context));

    topLevel->setGeometry(QRect(300, 300, 600, 600));

    auto geometry = sett.value("mainWindow/geometry");
    if (!geometry.isNull())
        topLevel->setGeometry(geometry.toRect());

    auto windowSatae = sett.value("mainWindow/windowState");
    if (!windowSatae.isNull())
        topLevel->setWindowState(static_cast<Qt::WindowState>(geometry.toInt()));

    topLevel->show();

    int ret = app.exec();

    sett.setValue("mainWindow/geometry", topLevel->geometry());
    sett.setValue("mainWindow/windowState", topLevel->windowState());
    sett.sync();

    thread.quit();
    thread.wait();

    return ret;
}
