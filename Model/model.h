#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <utility>
#include <QWidget>

#include "../View/view.h"
#include "constants.h"
#include "../Map/map.h"
#include "../GameObject/hero.h"
#include "../Util/vector.h"

class Model {
 public:
  explicit Model(std::unique_ptr<View>&& view);

  void MoveHero(Vector2D direction);

 private:
  std::pair<int, int> GetCellSize() const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point) const;

 private:
  std::unique_ptr<View> view_;
  Map map_;
  Hero hero_;
};

#endif  // MODEL_MODEL_H_
