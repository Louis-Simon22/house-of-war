#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QThread>

#include <iostream>

#include "../src/ui/control/modelthreadmanager.h"
#include "../src/ui/models/cellsmodel.h"
#include "../src/ui/models/charactersmodel.h"
#include "../src/ui/painters/segmentspainter.h"
#include "../src/ui/wrappers/characterdataqmlwrapper.h"
#include "../src/ui/wrappers/gamedatamanagerqmlwrapper.h"
#include "../src/ui/wrappers/worlddataqmlwrapper.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  const QString nonCreatableMessage = "This object may not be created in QML";

  // Registering c++ bindings for QML
  // Painters
  qmlRegisterType<::how::ui::SegmentsPainter>(
      "com.louissimonmcnicoll.how.ui.segmentspainter", 1, 0, "SegmentsPainter");
  // Models
  qmlRegisterUncreatableType<::how::ui::CellsModel>(
      "com.louissimonmcnicoll.how.ui.cellsmodel", 1, 0, "CellsModel",
      nonCreatableMessage);
  qmlRegisterUncreatableType<::how::ui::CharactersModel>(
      "com.louissimonmcnicoll.how.ui.charactersmodel", 1, 0, "CharactersModel",
      nonCreatableMessage);
  // QML wrappers
  qmlRegisterType<::how::ui::GameDataManagerQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.gamedatamanager", 1, 0, "GameDataManager");
  qmlRegisterUncreatableType<::how::ui::WorldDataQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.worlddata", 1, 0, "WorldData",
      nonCreatableMessage);
  qmlRegisterUncreatableType<::how::ui::CharacterDataQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.characterdata", 1, 0, "CharacterData",
      nonCreatableMessage);
  // Others
  qmlRegisterType<::how::ui::ModelThreadManager>(
      "com.louissimonmcnicoll.how.ui.modelthreadmanager", 1, 0,
      "ModelThreadManager");

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  std::cout << "Main thread " << app.thread() << std::endl;

  return app.exec();
}
