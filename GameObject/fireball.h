#ifndef GAMEOBJECT_FIREBALL_H_
#define GAMEOBJECT_FIREBALL_H_

#include "dynamic_object.h"
#include "../Util/vector.h"

class Fireball : public DynamicObject {
 public:
  Fireball(const Point& position, const Vector2D& direction) :
  DynamicObject(position), direction_(direction) {}

  void Move();

 private:
  Vector2D direction_;
};

#endif  // GAMEOBJECT_FIREBALL_H_
