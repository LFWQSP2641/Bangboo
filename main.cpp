#include "BangbooTranslater.h"
#include "QMLUtils.h"

#include <QFontDatabase>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QMLUtils utils;

    qmlRegisterSingletonInstance("QMLUtils", 1, 0, "QMLUtils", &utils);

    qmlRegisterType<BangbooTranslater>("BangbooTranslater", 1, 0, "BangbooTranslater");

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl)
        {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
