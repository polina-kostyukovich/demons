#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include "../Util/point.h"

class GameObject {
 public:
  explicit GameObject(const Point& position = {0, 0});

  void SetPosition(const Point& new_position);
  Point GetPosition() const;

 protected:
  Point position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
