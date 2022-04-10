#ifndef GAMEOBJECT_STATIC_OBJECT_H_
#define GAMEOBJECT_STATIC_OBJECT_H_

#include "game_object.h"

class StaticObject : public GameObject {
 public:
  explicit StaticObject(const Point& position = {0, 0});
};

#endif  // GAMEOBJECT_STATIC_OBJECT_H_
