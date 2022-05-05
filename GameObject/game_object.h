#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include "../Util/point.h"
#include "../Util/structs.h"

class GameObject {
 public:
  explicit GameObject(const Point& position = Point());

  void SetPosition(const Point& new_position);
  void SetPositionX(long double new_x);
  void SetPositionY(long double new_y);

  Point GetPosition() const;

  virtual Picture GetPicture(int counter) const = 0;

 protected:
  Point position_;
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
