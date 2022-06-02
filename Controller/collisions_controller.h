#ifndef CONTROLLER_COLLISIONS_CONTROLLER_H_
#define CONTROLLER_COLLISIONS_CONTROLLER_H_

#include <memory>
#include <vector>

#include "../GameObject/boiler.h"
#include "../GameObject/fireball.h"
#include "../GameObject/hero.h"
#include "../GameObject/npc.h"
#include "../Model/model.h"
#include "../Util/point.h"

class CollisionsController {
 public:
  bool SomeoneWasKilled() const;

  void CheckCollisions(const std::unique_ptr<Model>& model,
                       const Point& old_hero_pos,
                       const std::vector<Point>& old_npcs_pos,
                       int window_width, int window_height);

  void PrepareForDrawing(const std::unique_ptr<Model>& model);

 private:
  void CheckFireballsWithWalls(const std::unique_ptr<Model>& model,
                               int window_width, int window_height);

  void CheckHeroAndStaticObjects(const std::unique_ptr<Model>& model,
                                 const Point& old_hero_position);
  void CheckHeroAndStaticObject(const std::unique_ptr<Model>& model,
                                const Point& old_hero_position,
                                const std::shared_ptr<StaticObject>& object);

  void CheckFireballsAndStaticObjects(const std::unique_ptr<Model>& model);

  void CheckFireballsAndNpcs(const std::unique_ptr<Model>& model);

  void CheckHeroAndNpcs(const std::unique_ptr<Model>& model,
                        const Point& old_hero_pos,
                        const std::vector<Point>& old_npcs_pos);

  void ResetAllRenderingLevels(const std::vector<GameObject*>& all_objects);

  bool AreAllRenderingLevelsNumerated(
      const std::vector<GameObject*>& all_objects) const;
  void NumerateAllRenderingLevels(const std::vector<GameObject*>& all_objects);

 private:
  bool someone_was_killed_{false};
};

#endif  // CONTROLLER_COLLISIONS_CONTROLLER_H_
