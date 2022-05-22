#ifndef CONTROLLER_COLLISIONS_CONTROLLER_H_
#define CONTROLLER_COLLISIONS_CONTROLLER_H_

#include <memory>
#include <vector>

#include "../GameObject/boiler.h"
#include "../GameObject/fireball.h"
#include "../GameObject/hero.h"
#include "../GameObject/npc.h"
#include "../Util/point.h"

class CollisionsController {
 public:
  void CheckHeroAndStaticObjects(
      Hero* hero,
      const Point& old_hero_position,
      const std::vector<std::shared_ptr<StaticObject>>& objects);

  void CheckHeroAndStaticObject(Hero* hero,
                                const Point& old_hero_position,
                                const std::shared_ptr<StaticObject>& object);

  void CheckFireballsAndStaticObjects(
      std::vector<Fireball>* fireballs,
      const std::vector<std::shared_ptr<StaticObject>>& object);

  void CheckFireballsAndStaticObject(
      std::vector<Fireball>* fireballs,
      const std::shared_ptr<StaticObject>& object);

  void CheckFireballsAndNpcs(std::vector<Fireball>* fireballs,
                             std::vector<Npc>* objects);

  void CheckFireballsAndNpc(std::vector<Fireball>* fireballs, const Npc& npc);

  void CheckHeroAndNpcs(Hero* hero,
                        std::vector<Npc>* npcs,
                        const Point& old_hero_pos,
                        const std::vector<Point>& old_npcs_pos);

  void CheckHeroAndNpc(Hero* hero,
                       Npc* npc,
                       const Point& old_hero_pos,
                       const Point& old_npcs_pos);

  void CheckNpcAndStaticObjects(
      std::vector<Npc>* npcs,
      const std::vector<std::shared_ptr<StaticObject>>& objects);

  void CheckNpcAndStaticObject(Npc* npc, std::shared_ptr<StaticObject> object);
};

#endif  // CONTROLLER_COLLISIONS_CONTROLLER_H_
