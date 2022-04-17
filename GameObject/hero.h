#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"
#include "../Util/vector.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point());

  void Move(const Vector2D& direction, int window_width, int window_height);
};

#endif  // GAMEOBJECT_HERO_H_
