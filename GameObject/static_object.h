#ifndef GAMEOBJECT_STATIC_OBJECT_H_
#define GAMEOBJECT_STATIC_OBJECT_H_

#include "game_object.h"
#include "../Util/structs.h"

class StaticObject : public GameObject {
 public:
  explicit StaticObject(const Point& position = Point());

  virtual Picture GetPicture() const = 0;

  const HitBox& GetTopHitBox() const;

  void SetIsOverSomething(bool is_over_hero);
  bool IsOverSomething() const;

 protected:
  bool is_over_something{false};
  HitBox picture_above_hit_box_;
};

#endif  // GAMEOBJECT_STATIC_OBJECT_H_
