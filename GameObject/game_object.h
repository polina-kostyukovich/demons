#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include "../Util/point.h"

class GameObject {
 public:
  explicit GameObject(const Point& point);
  void SetPoint(const Point& new_point);
  Point GetPoint() const;

 private:
  Point point_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
