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
  Model() = default;
  
  const Hero& GetHero();
  void MoveHero(Vector2D direction);

 private:
  std::pair<int, int> GetCellSize() const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point) const;

 private:
  std::unique_ptr<View> view_ = nullptr;
  Hero hero_;
  Map map_{0, 0};
};

#endif  // MODEL_MODEL_H_
