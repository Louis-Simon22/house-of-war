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

#include "../src/ui/control/modelcontroller.h"
#include "../src/ui/control/modelcontroller.h"
#include "../src/ui/painters/segmentspainter.h"

Q_DECLARE_METATYPE(::how::model::InteractiveEntity *)

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
      "com.louissimonmcnicoll.how.ui.entitycontroller", 1, 0,
      "EntityController", uncreatableTypeErrorMessage);
  qmlRegisterType<::how::ui::ModelController>(
      "com.louissimonmcnicoll.how.ui.modelcontroller", 1, 0, "ModelController");
  qmlRegisterType<::how::ui::ModelController>(
      "com.louissimonmcnicoll.how.ui.modelcontroller", 1, 0, "ModelController");
  qRegisterMetaType<::how::model::InteractiveEntity *>("InteractiveEntity");

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  std::cout << "Main thread " << app.thread() << std::endl;

  return app.exec();
}
