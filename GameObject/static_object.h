#ifndef GAMEOBJECT_STATIC_OBJECT_H_
#define GAMEOBJECT_STATIC_OBJECT_H_

#include "game_object.h"
#include "../Util/structs.h"

class StaticObject : public GameObject {
 public:
  explicit StaticObject(const Point& position = Point());

  virtual Picture GetPicture() const = 0;

  const HitBox& GetTopHitBox() const;

  void SetIsOverHero(bool is_over_hero);
  bool IsOverHero() const;

 protected:
  bool is_over_hero_{false};
  HitBox top_hit_box_;
};

#endif  // GAMEOBJECT_STATIC_OBJECT_H_
