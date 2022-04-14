#ifndef GAMEOBJECT_HIT_BOX_H_
#define GAMEOBJECT_HIT_BOX_H_

#include <memory>

#include "../Util/point.h"

struct Rect {
  Rect(const Point& left_upper_coordinates,
       const Point& right_lower_coordinates) :
  left_upper_coords(left_upper_coordinates),
  right_lower_coords(right_lower_coordinates) {}

  Point left_upper_coords;
  Point right_lower_coords;
};

class HitBox {
 public:
  HitBox() = default;
  HitBox(const Point& pos, double width, double height);

  Rect GetRect() const;

  bool IsCollided(const HitBox& other_hit_box) const;
  bool IsCollided(const Rect& other_rect) const;

 private:
  Point pos_;  // object position
  double size_{0};  // the size of the object
  double width_{0};
  double height_{0};
};

#endif  // GAMEOBJECT_HIT_BOX_H_
