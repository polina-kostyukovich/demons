#ifndef GAMEOBJECT_HIT_BOX_H_
#define GAMEOBJECT_HIT_BOX_H_

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
  HitBox(const Point* pos, double width, double height) :
  pos_(pos), width_(width), height_(height) {}

  Rect GetRect() const;

  bool IsCollided(const HitBox& other_hit_box) const;
  bool IsCollided(const Rect& other_rect) const;

 private:
  const Point* pos_; // object_position
  double width_{0};
  double height_{0};
};

#endif  // GAMEOBJECT_HIT_BOX_H_
