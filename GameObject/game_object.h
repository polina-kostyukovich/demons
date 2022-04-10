#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include "../Util/point.h"

class GameObject {
 public:
  explicit GameObject(const Point& point);
  void SetPosition(const Point& new_point);
  Point GetPosition() const;

 private:
  Point position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
