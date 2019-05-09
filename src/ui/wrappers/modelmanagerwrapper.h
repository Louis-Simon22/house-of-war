#ifndef GAMEDATAMANAGERQMLWRAPPER_H
#define GAMEDATAMANAGERQMLWRAPPER_H

#include <QObject>
#include <QQuickItem>
#include <QRect>

#include "../../model/managers/modelmanager.h"

namespace how {
namespace ui {
// TODO change to WorldManagerWrapper
class ModelManagerWrapper : public QObject {
  Q_OBJECT

  // TODO maybe move this to the main controller?
  Q_PROPERTY(
      QRect worldBounds READ getWorldBounds NOTIFY newModelGenerated FINAL)

public:
  ModelManagerWrapper(model::ModelManager *modelManagerPtr);

signals:
  void newModelGenerated();

public slots:
  void newModel(int width, int height, float minimumVoronoiCellDistance,
                int randomSeed);

private:
  QRect getWorldBounds() const;

private:
  model::ModelManager *modelManagerPtr;
};
} // namespace ui
} // namespace how

#endif // GAMEDATAMANAGERQMLBINDINGS_H
