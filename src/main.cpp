#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQmlEngine>
#include <QSurfaceFormat>
#include <QThread>

#include <iostream>

#define BOOST_UUID_NO_SIMD
#define BOOST_UUID_NO_TYPE_TRAITS
// Remove this define when boost is updated to 1.70
#define BOOST_ALLOW_DEPRECATED_HEADERS

// Debug output of qml renderer
#define QSG_RENDERER_DEBUG = render

#include "../src/ui/control/modelthreadmanager.h"
#include "../src/ui/models/charactersmodel.h"
#include "../src/ui/models/voronoicellsmodel.h"
#include "../src/ui/painters/segmentspainter.h"
#include "../src/ui/painters/tilepainter.h"
#include "../src/ui/wrappers/graphentitymanagerqmlwrapper.h"
#include "../src/ui/wrappers/modelmanagerqmlwrapper.h"
#include "../src/ui/wrappers/worldmanagerqmlwrapper.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

//  QSurfaceFormat format;
//  format.setSamples(16);
//  QSurfaceFormat::setDefaultFormat(format);
  QQmlApplicationEngine engine;

  const QString uncreatableTypeErrorMessage =
      "This object may not be created in QML";

  // Registering c++ bindings for QML
  // Painters
  qmlRegisterType<::how::ui::SegmentsPainter>(
      "com.louissimonmcnicoll.how.ui.segmentspainter", 1, 0, "SegmentsPainter");
  qmlRegisterType<::how::ui::TilePainter>(
      "com.louissimonmcnicoll.how.ui.TilePainter", 1, 0, "TilePainter");
  // Models
  qmlRegisterUncreatableType<::how::ui::VoronoiCellsModel>(
      "com.louissimonmcnicoll.how.ui.voronoicellsmodel", 1, 0,
      "VoronoiCellsModel", uncreatableTypeErrorMessage);
  qmlRegisterUncreatableType<::how::ui::CharactersModel>(
      "com.louissimonmcnicoll.how.ui.charactersmodel", 1, 0, "CharactersModel",
      uncreatableTypeErrorMessage);
  // QML wrappers
  qmlRegisterType<::how::ui::ModelManagerQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.modelmanager", 1, 0, "ModelManager");
  qmlRegisterUncreatableType<::how::ui::WorldManagerQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.worldmanager", 1, 0, "WorldManager",
      uncreatableTypeErrorMessage);
  qmlRegisterUncreatableType<::how::ui::GraphEntityManagerQMLWrapper>(
      "com.louissimonmcnicoll.how.ui.graphentitymanager", 1, 0, "GraphEntityManager",
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
