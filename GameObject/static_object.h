#ifndef GAMEOBJECT_STATIC_OBJECT_H_
#define GAMEOBJECT_STATIC_OBJECT_H_

#include "game_object.h"
#include "../Util/structs.h"

class StaticObject : public GameObject {
 public:
  explicit StaticObject(const Point& position, int width, int height);

  int GetWidth() const;
  int GetHeight() const;

 protected:
  int width_;
  int height_;
};

#endif  // GAMEOBJECT_STATIC_OBJECT_H_
