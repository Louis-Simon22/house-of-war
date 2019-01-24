#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <vector>
#include <memory>
#include "../model/modelfacade.h"

namespace how {
namespace control {
namespace bg = ::boost::geometry;
class GameManager {
  using ModelFacade = ::how::model::ModelFacade;
  using WorldGenerationConfig = ::how::model::types::WorldGenerationConfig;

 public:
  explicit GameManager();

  void generateNewWorld(const WorldGenerationConfig& config);

  const std::vector<::how::model::types::point_t>* getPointsList() const;
  const std::vector<::how::model::types::segment_t> *getOutlineSegments() const;
  const ::how::model::types::box_t getWorldBounds() const;

 private:
  std::unique_ptr<ModelFacade> modelFacadePtr;
};
}  // namespace control
}  // namespace how
#endif
