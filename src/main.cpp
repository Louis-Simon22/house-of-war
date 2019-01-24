#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../src/bind/gamemanagerqmlbindings.h"
#include "../src/bind/models/worldmodel.h"
#include "../src/bind/painters/celloutlinepainter.h"

int main(int argc, char* argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  // Register c++ bindings for QML
  qmlRegisterType<::how::bind::WorldModel>(
      "com.louissimonmcnicoll.how.bind.worldmodel", 1, 0, "WorldModel");
  qmlRegisterType<::how::bind::CellOutlinePainter>(
              "com.louissimonmcnicoll.how.bind.celloutlinepainter", 1, 0, "CellOutlinePainter");
  qmlRegisterType<::how::bind::GameManagerQMLBindings>(
      "com.louissimonmcnicoll.how.bind.gamemanager", 1, 0, "GameManager");

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  return app.exec();
}
