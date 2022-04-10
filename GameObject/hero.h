#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = {0, 0});
};

#endif  // GAMEOBJECT_HERO_H_
