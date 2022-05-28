#ifndef GAMEOBJECT_STATIC_OBJECT_H_
#define GAMEOBJECT_STATIC_OBJECT_H_

#include "game_object.h"
#include "../Util/structs.h"

class StaticObject : public GameObject {
 public:
  explicit StaticObject(const Point& position = Point());
};

#endif  // GAMEOBJECT_STATIC_OBJECT_H_
