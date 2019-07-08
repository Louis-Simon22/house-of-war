#include <QGuiApplication>
#include <QMetaType>
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

#include "./ui/control/modelcontroller.h"

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
  // Controllers
  qmlRegisterUncreatableType<::how::ui::EntitiesController>(
      "com.louissimonmcnicoll.how.ui.entitiescontroller", 1, 0,
      "EntitiesController", uncreatableTypeErrorMessage);
  qmlRegisterType<::how::ui::ModelController>(
      "com.louissimonmcnicoll.how.ui.modelcontroller", 1, 0, "ModelController");
  qmlRegisterUncreatableType<::how::ui::TilesController>(
      "com.louissimonmcnicoll.how.ui.tilescontroller", 1, 0, "TilesController",
      uncreatableTypeErrorMessage);
  // Bindings
  qmlRegisterUncreatableType<::how::ui::TileBindings>(
      "com.louissimonmcnicoll.how.ui.tilebindings", 1, 0, "TileBindings",
      uncreatableTypeErrorMessage);
  qmlRegisterUncreatableType<::how::ui::ArmyBindings>(
      "com.louissimonmcnicoll.how.ui.armybindings", 1, 0, "ArmyBindings",
      uncreatableTypeErrorMessage);
  // ENUMS
  qmlRegisterUncreatableType<::how::ui::TileDisplayStatusWrapper>(
      "com.louissimonmcnicoll.how.ui.tiledisplaystatuswrapper", 1, 0,
      "TileDisplayStatusWrapper", uncreatableTypeErrorMessage);

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  std::cout << "Main thread " << app.thread() << std::endl;

  return app.exec();
}
