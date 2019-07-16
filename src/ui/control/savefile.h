#ifndef SAVEFILE_H
#define SAVEFILE_H

#include <QObject>
#include <QString>

namespace how {
namespace ui {
class SaveFile : public QObject {
  Q_OBJECT

  Q_PROPERTY(QString name MEMBER name CONSTANT)

public:
  explicit SaveFile(QString name);

private:
  QString name;
};
} // namespace ui
} // namespace how

#endif // SAVEFILE_H
