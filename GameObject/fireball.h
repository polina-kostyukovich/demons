#ifndef GAMEOBJECT_FIREBALL_H_
#define GAMEOBJECT_FIREBALL_H_

#include <vector>

#include "dynamic_object.h"
#include "../Util/vector.h"
#include "../Util/structs.h"

class Fireball : public DynamicObject {
 public:
  Fireball(const Point& position, const Vector2D& direction) :
  DynamicObject(position), direction_(direction) {}

  void LoadPicture();
  Picture GetPicture() const;

  void Move();

 private:
  Vector2D direction_;
  std::vector<QPixmap> pixmaps_;
};

#endif  // GAMEOBJECT_FIREBALL_H_
