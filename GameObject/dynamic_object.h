#ifndef GAMEOBJECT_DYNAMIC_OBJECT_H_
#define GAMEOBJECT_DYNAMIC_OBJECT_H_

#include "game_object.h"

class DynamicObject : public GameObject {
 public:
  explicit DynamicObject(const Point& position = {0, 0});
};

#endif  // GAMEOBJECT_DYNAMIC_OBJECT_H_
