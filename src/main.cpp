#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../src/bind/gamemanagerqmlbindings.h"
#include "../src/bind/models/worldmodel.h"
#include "../src/bind/painters/celloutlinespainter.h"
#include "../src/bind/painters/pathspainter.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  // Register c++ bindings for QML
  qmlRegisterType<::how::bind::CellOutlinesPainter>(
              "com.louissimonmcnicoll.how.bind.celloutlinespainter", 1, 0, "CellOutlinesPainter");
  qmlRegisterType<::how::bind::PathsPainter>(
              "com.louissimonmcnicoll.how.bind.pathspainter", 1, 0, "PathsPainter");
  qmlRegisterType<::how::bind::WorldModel>(
      "com.louissimonmcnicoll.how.bind.worldmodel", 1, 0, "WorldModel");
  qmlRegisterType<::how::bind::GameManagerQMLBindings>(
      "com.louissimonmcnicoll.how.bind.gamemanager", 1, 0, "GameManager");

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
