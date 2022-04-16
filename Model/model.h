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

  Hero& GetHero();

 private:
  std::pair<int, int> GetCellSize(int window_width, int window_height) const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point,
                                              int window_width,
                                              int window_height) const;

 private:
  Hero hero_;
  Map map_{0, 0};
};

#endif  // MODEL_MODEL_H_
