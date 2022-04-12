#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include "dynamic_object.h"

class Creature : public DynamicObject {
 public:
  explicit Creature(const Point& position = {0, 0});
};

#endif  // GAMEOBJECT_CREATURE_H_
