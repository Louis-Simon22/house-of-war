#ifndef SELECTABLEENTITYWRAPPER_H
#define SELECTABLEENTITYWRAPPER_H

#include "./entitywrapper.h"

namespace how {
namespace ui {
class SelectableEntityWrapper : public EntityWrapper {
public:
  SelectableEntityWrapper();
  ~SelectableEntityWrapper() override;

public:
  bool isSelectable() const override;

public:
  bool isSelected() const;
  void setSelected(bool selected);

private:
  bool selected;
};
} // namespace ui
} // namespace how

#endif // SELECTABLEENTITYWRAPPER_H
