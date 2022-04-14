#include "hit_box.h"

HitBox::Rect HitBox::GetRect() const {
  Point left_upper_coords(pos_.GetX() - hit_box_width_ / 2,
                          pos_.GetY() - hit_box_height_ / 2 +
                          object_height_ / 2);
  Point right_lower_coords(pos_.GetX() + hit_box_width_ / 2,
                           pos_.GetY() + hit_box_height_ / 2
                           + object_height_ / 2);

  return Rect(left_upper_coords, right_lower_coords);
}

bool HitBox::IsCollided(const HitBox& other_hit_box) const {
  Rect our_rectangle = GetRect();
  Rect other_rect = other_hit_box.GetRect();
  bool is_intersected_along_x_axis =
      !(other_rect.left_upper_coords.GetX() -
          our_rectangle.right_lower_coords.GetX() > constants::kEpsilon ||
          our_rectangle.left_upper_coords.GetX() -
              other_rect.right_lower_coords.GetX() > constants::kEpsilon);

  bool is_intersected_along_y_axis =
      !(other_rect.left_upper_coords.GetY() -
          our_rectangle.right_lower_coords.GetY() > constants::kEpsilon ||
          our_rectangle.left_upper_coords.GetY() -
              other_rect.right_lower_coords.GetY() > constants::kEpsilon);

  return (is_intersected_along_x_axis && is_intersected_along_y_axis);
}
