#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QThread>

#include <iostream>

#define BOOST_UUID_NO_SIMD
#define BOOST_UUID_NO_TYPE_TRAITS
// Remove this define when boost is updated to 1.70
#define BOOST_ALLOW_DEPRECATED_HEADERS

#include "../src/ui/control/modelthreadmanager.h"
#include "../src/ui/models/charactersmodel.h"
#include "../src/ui/models/voronoicellsmodel.h"
#include "../src/ui/painters/segmentspainter.h"
#include "../src/ui/painters/cellspainter.h"
#include "../src/ui/wrappers/characterdataqmlwrapper.h"
#include "../src/ui/wrappers/gamedatamanagerqmlwrapper.h"
#include "../src/ui/wrappers/worlddataqmlwrapper.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);
  QQmlApplicationEngine engine;

  const QString uncreatableTypeErrorMessage =
      "This object may not be created in QML";

  // Registering c++ bindings for QML
  // Painters
  qmlRegisterType<::how::ui::SegmentsPainter>(
      "com.louissimonmcnicoll.how.ui.segmentspainter", 1, 0, "SegmentsPainter");
  qmlRegisterType<::how::ui::CellsPainter>(
              "com.louissimonmcnicoll.how.ui.cellspainter", 1, 0, "CellsPainter");
  // Models
  qmlRegisterUncreatableType<::how::ui::VoronoiCellsModel>(
      "com.louissimonmcnicoll.how.ui.voronoicellsmodel", 1, 0,
      "VoronoiCellsModel", uncreatableTypeErrorMessage);
  qmlRegisterUncreatableType<::how::ui::CharactersModel>(
      "com.louissimonmcnicoll.how.ui.charactersmodel", 1, 0, "CharactersModel",
      uncreatableTypeErrorMessage);
  // QML wrappers
  qmlRegisterType<::how::ui::GameDataManagerQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.gamedatamanager", 1, 0, "GameDataManager");
  qmlRegisterUncreatableType<::how::ui::WorldDataQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.worlddata", 1, 0, "WorldData",
      uncreatableTypeErrorMessage);
  qmlRegisterUncreatableType<::how::ui::CharacterDataQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.characterdata", 1, 0, "CharacterData",
      uncreatableTypeErrorMessage);
  // Controllers
  qmlRegisterUncreatableType<::how::ui::CharactersController>(
      "com.louissimonmcnicoll.how.ui.characterscontroller", 1, 0,
      "CharactersController", uncreatableTypeErrorMessage);
  // Others
  qmlRegisterUncreatableType<::how::ui::ModelThreadManager>(
      "com.louissimonmcnicoll.how.ui.modelthreadmanager", 1, 0,
      "ModelThreadManager", uncreatableTypeErrorMessage);

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  std::cout << "Main thread " << app.thread() << std::endl;

  return app.exec();
}
