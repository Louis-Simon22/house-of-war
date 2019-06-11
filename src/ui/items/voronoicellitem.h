#ifndef VORONOICELLITEM_H
#define VORONOICELLITEM_H

#include "../../model/entities/voronoicell.h"
#include "../../model/modeltypes.h"
#include "../painters/painteritem.h"
#include "../painters/polygonpainter.h"
#include "./interactiveentityitem.h"

namespace how {
namespace ui {
class VoronoiCellItem : public InteractiveEntityItem {
  Q_OBJECT

public:
  VoronoiCellItem(std::shared_ptr<model::VoronoiCell> voronoiCellPtr,
                  QQuickItem *parent);

signals:
  void onVoronoiCellItemSelected(VoronoiCellItem *voronoiCellItem);

public slots:
  void onInteractiveItemSelected() override;

private slots:
  void onGraphEntityUpdated() override;

public:
  model::VoronoiCell *getVoronoiCell();

private:
  std::shared_ptr<model::VoronoiCell> voronoiCellPtr;
  PolygonPainter *voronoiCellPainter;
};
} // namespace ui
} // namespace how

#endif // VORONOICELLITEM_H
