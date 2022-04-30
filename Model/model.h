#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <utility>
#include <QWidget>

#include "constants.h"
#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Util/vector.h"

class Model {
 public:
  Model() = default;

  Hero& GetHero();
  Map& GetMap();

  void LoadPictures();

 private:
  std::pair<int, int> GetCellSize(int window_width, int window_height) const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point,
                                              int window_width,
                                              int window_height) const;

 private:
  Hero hero_;
  Map map_;
};

#endif  // MODEL_MODEL_H_
