#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "control/gamemanager.h"
#include "model/geography/worldmodel.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register c++ bindings for QML
    qmlRegisterType<WorldModel>("worldmodel", 1, 0, "WorldModel");
    qmlRegisterType<GameManager>("gamemanager", 1, 0, "GameManager");

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}
