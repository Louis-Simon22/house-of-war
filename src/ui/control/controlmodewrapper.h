#ifndef CONTROLMODE_H
#define CONTROLMODE_H

#include <QObject>

namespace how {
namespace ui {
class ControlModeWrapper final : public QObject {
  Q_GADGET

private:
  ControlModeWrapper();

public:
  enum ControlMode { PLAY = 0, EDIT, DEFAULT = PLAY };
  Q_ENUM(ControlMode);
};
} // namespace ui
} // namespace how

#endif // CONTROLMODE_H
