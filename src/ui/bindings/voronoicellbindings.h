#ifndef OVERLAYTILEBINDINGS_H
#define OVERLAYTILEBINDINGS_H

#include <QObject>

#include "../items/voronoicellitem.h"

namespace how {
namespace ui {
class VoronoiCellBindings : public QObject {
  Q_OBJECT

  Q_PROPERTY(bool isBound READ isBound NOTIFY updateBindings)
  Q_PROPERTY(float altitude READ getAltitude NOTIFY updateBindings)

public:
  VoronoiCellBindings();

signals:
  void updateBindings();

public slots:
  void onVoronoiCellItemSelected(VoronoiCellItem *voronoiCellItem);

private:
  bool isBound() const;
  types::carac_t getAltitude() const;

private:
  VoronoiCellItem *voronoiCellItem;
};
} // namespace ui
} // namespace how

#endif // TILEBINDINGS_H
