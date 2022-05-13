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
  explicit HitBox(const Point& pos,
                  double vertical_shift = 0,
                  double width = 0,
                  double height = 0) :
      pos_(pos), vertical_shift_(vertical_shift), hit_box_width_(width),
      hit_box_height_(height) {}

  void SetVerticalShift(long double shift);
  void SetWidth(long double width);
  void SetHeight(long double height);

  long double GetVerticalShift() const;
  long double GetWidth() const;
  long double GetHeight() const;

  bool IsCollided(const HitBox& other_hit_box) const;

 private:
  Rect GetRect() const;

  const Point& pos_;
  long double vertical_shift_{0};
  long double hit_box_width_{0};
  long double hit_box_height_{0};
};

#endif  // UTIL_HIT_BOX_H_
