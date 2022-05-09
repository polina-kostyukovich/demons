#ifndef MODEL_MODEL_H_
#define MODEL_MODEL_H_

#include <memory>
#include <utility>
#include <QWidget>

#include "constants.h"
#include "../Controller/npc_controller.h"
#include "../GameObject/hero.h"
#include "../Map/map.h"
#include "../Util/vector.h"

class Model {
 public:
  Model() = default;

  const Hero& GetHero() const;
  Hero& GetHero();

  const Map& GetMap() const;
  Map& GetMap();

  const NpcController& GetNpcController() const;
  NpcController& GetNpcController();

  void LoadPictures();

 private:
  std::pair<int, int> GetCellSize(int window_width, int window_height) const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point,
                                              int window_width,
                                              int window_height) const;

 private:
  Hero hero_;
  Map map_;
  NpcController npc_controller_;
};

#endif  // MODEL_MODEL_H_
