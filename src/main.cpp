#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "control/gamemanager.h"
#include "model/world/worldmodel.h"

int main(int argc, char *argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    // Register c++ bindings for QML
    qmlRegisterType<WorldModel>("worldmodel", 1, 0, "WorldModel");
    qmlRegisterType<GameManager>("gamemanager", 1, 0, "GameManager");

    engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
    if (engine.rootObjects().isEmpty())
    {
        return -1;
    }

    return app.exec();
}

