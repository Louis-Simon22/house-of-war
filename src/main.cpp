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

#include "../src/ui/control/entitycontroller.h"
#include "../src/ui/control/maincontroller.h"
#include "../src/ui/control/modelthreadmanager.h"
#include "../src/ui/models/entitiesmodel.h"
#include "../src/ui/painters/armypainter.h"
#include "../src/ui/painters/characterpainter.h"
#include "../src/ui/painters/segmentspainter.h"
#include "../src/ui/painters/voronoicellpainter.h"
#include "../src/ui/wrappers/worldmanagerwrapper.h"

int main(int argc, char *argv[]) {
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(8);
  QSurfaceFormat::setDefaultFormat(format);
  QQmlApplicationEngine engine;

  const QString uncreatableTypeErrorMessage =
      "This object may not be created in QML";

  // Registering c++ bindings for QML
  // Painters
  qmlRegisterUncreatableType<::how::ui::SegmentsPainter>(
      "com.louissimonmcnicoll.how.ui.segmentspainter", 1, 0, "SegmentsPainter",
      uncreatableTypeErrorMessage);
  // Models
  qmlRegisterUncreatableType<::how::ui::EntitiesModel>(
      "com.louissimonmcnicoll.how.ui.entitiesmodel", 1, 0, "EntitiesModel",
      uncreatableTypeErrorMessage);
  // QML wrappers
  qmlRegisterUncreatableType<::how::ui::WorldManagerWrapper>(
      "com.louissimonmcnicoll.how.ui.worldmanager", 1, 0, "WorldManager",
      uncreatableTypeErrorMessage);
  // Controllers
  qmlRegisterUncreatableType<::how::ui::EntityController>(
      "com.louissimonmcnicoll.how.ui.entitycontroller", 1, 0,
      "EntityController", uncreatableTypeErrorMessage);
  qmlRegisterType<::how::ui::MainController>(
      "com.louissimonmcnicoll.how.ui.maincontroller", 1, 0, "MainController");
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
