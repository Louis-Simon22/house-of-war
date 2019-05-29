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

#include "../src/ui/control/graphentitycontroller.h"
#include "../src/ui/control/maincontroller.h"
#include "../src/ui/control/modelthreadmanager.h"
#include "../src/ui/painters/segmentspainter.h"

Q_DECLARE_METATYPE(::how::model::GraphEntity *)

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
  qmlRegisterUncreatableType<::how::ui::GraphEntityController>(
      "com.louissimonmcnicoll.how.ui.entitycontroller", 1, 0,
      "EntityController", uncreatableTypeErrorMessage);
  qmlRegisterType<::how::ui::MainController>(
      "com.louissimonmcnicoll.how.ui.maincontroller", 1, 0, "MainController");
  qmlRegisterType<::how::ui::ModelController>(
      "com.louissimonmcnicoll.how.ui.modelcontroller", 1, 0, "ModelController");
  // Others
  qmlRegisterUncreatableType<::how::ui::ModelThreadManager>(
      "com.louissimonmcnicoll.how.ui.modelthreadmanager", 1, 0,
      "ModelThreadManager", uncreatableTypeErrorMessage);
  qRegisterMetaType<::how::model::GraphEntity *>("GraphEntityPtr");

  engine.load(QUrl(QStringLiteral("qrc:/qml/Window.qml")));
  if (engine.rootObjects().isEmpty()) {
    return -1;
  }

  std::cout << "Main thread " << app.thread() << std::endl;

  return app.exec();
}
