#ifndef ARMYBINDINGS_H
#define ARMYBINDINGS_H

#include <QObject>

#include "../items/armyitem.h"

namespace how {
namespace ui {
class ArmyBindings : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool isBound READ isBound NOTIFY updateBindings)
  Q_PROPERTY(float size READ getSize NOTIFY updateBindings)

public:
  ArmyBindings();

signals:
  void updateBindings();

public slots:
  void onArmyItemSelected(ArmyItem *armyItem);

private:
  bool isBound() const;
  types::carac_t getSize() const;

private:
  ArmyItem *armyItem;
};
} // namespace ui
} // namespace how

#endif // ARMYBINDINGS_H
