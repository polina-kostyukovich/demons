#ifndef CONTROLLER_COLLISIONS_CONTROLLER_H_
#define CONTROLLER_COLLISIONS_CONTROLLER_H_

#include "../GameObject/boiler.h"
#include "../GameObject/hero.h"
#include "../Util/point.h"

class CollisionsController {
 public:
  void CheckHeroAndStaticObjects(
      Hero& hero,
      const Point& old_hero_position,
      const std::vector<std::shared_ptr<StaticObject>>& objects);

  void CheckHeroAndStaticObject(Hero& hero,
                                const Point& old_hero_position,
                                const std::shared_ptr<StaticObject>& object);
};

#endif  // CONTROLLER_COLLISIONS_CONTROLLER_H_
