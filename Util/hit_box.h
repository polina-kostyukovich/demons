#ifndef UTIL_HIT_BOX_H_
#define UTIL_HIT_BOX_H_

#include <memory>

#include "point.h"

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
  HitBox(const Point& pos, double object_height, double width, double height) :
      pos_(pos), object_height_(object_height), hit_box_width_(width),
      hit_box_height_(height) {}

  bool IsCollided(const HitBox& other_hit_box) const;

 private:
  Rect GetRect() const;

  const Point& pos_;
  double object_height_{0};
  double hit_box_width_{0};
  double hit_box_height_{0};
};

#endif  // UTIL_HIT_BOX_H_
