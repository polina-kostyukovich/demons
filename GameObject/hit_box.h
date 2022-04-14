#ifndef GAMEOBJECT_HIT_BOX_H_
#define GAMEOBJECT_HIT_BOX_H_

#include <memory>

#include "../Util/point.h"

class HitBox {
 private:
  struct Rect {
    Rect(const Point& left_upper_coordinates,
         const Point& right_lower_coordinates) :
        left_upper_coords(left_upper_coordinates),
        right_lower_coords(right_lower_coordinates) {}

    Point left_upper_coords;
    Point right_lower_coords;
  };

 public:
  HitBox() = default;
  HitBox(const Point& pos, double width, double height) :
      pos_(pos), hit_box_width_(width), hit_box_height_(height) {}

  Rect GetRect() const;

  bool IsCollided(const HitBox& other_hit_box) const;

 private:
  const Point& pos_;  // object position
  double object_height_{0};  // the height of the object
  double hit_box_width_{0};
  double hit_box_height_{0};
};

#endif  // GAMEOBJECT_HIT_BOX_H_
