#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "morsecode.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    MorseCode morseCodeTranslator;

    engine.rootContext()->setContextProperty("translator", &morseCodeTranslator);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
