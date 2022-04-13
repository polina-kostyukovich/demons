#include "hit_box.h"

HitBox::HitBox(const Point& pos, double width, double height) {
  pos_ = pos;
  width_ = width;
  height_ = height;
}

Rect HitBox::GetRect() const {
  double half_width = width_ / 2;
  double half_height = height_ / 2;

  Point left_upper_coords(pos_.GetX() - half_width, pos_.GetY() - half_height);
  Point right_lower_coords(pos_.GetX() + half_width,
                           pos_.GetY() + half_height);
  return Rect(left_upper_coords, right_lower_coords);
}

bool HitBox::IsCollided(const Rect& other_rect) const {
  Rect our_rectangle = GetRect();
  return ((other_rect.left_upper_coords.GetX() -
      our_rectangle.right_lower_coords.GetX() <= constants::kEpsilon ||
      our_rectangle.left_upper_coords.GetX() -
      other_rect.right_lower_coords.GetX() <= constants::kEpsilon) &&
      (other_rect.left_upper_coords.GetY() -
      our_rectangle.right_lower_coords.GetY() <= constants::kEpsilon ||
      our_rectangle.left_upper_coords.GetY() -
      other_rect.right_lower_coords.GetY() <= constants::kEpsilon));
      // (other.x1 <= our.x2 || our.x1 <= other.x2) &&
      // (other.y1 <= our.y2 || our.y1 <= other.y2)
}

bool HitBox::IsCollided(const HitBox& other_hit_box) const {
  return IsCollided(other_hit_box.GetRect());
}
