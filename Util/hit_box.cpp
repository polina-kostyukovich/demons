#include "hit_box.h"

void HitBox::SetVerticalShift(long double shift) {
  vertical_shift_ = shift;
}

void HitBox::SetWidth(long double width) {
  hit_box_width_ = width;
}

void HitBox::SetHeight(long double height) {
  hit_box_height_ = height;
}

long double HitBox::GetWidth() const {
  return hit_box_width_;
}

long double HitBox::GetHeight() const {
  return hit_box_height_;
}

long double HitBox::GetVerticalShift() const {
  return vertical_shift_;
}

bool HitBox::IsCollided(const HitBox& other_hit_box) const {
  Rect our_rect = GetRect();
  Rect other_rect = other_hit_box.GetRect();
  bool is_intersected_along_x_axis =
      !(other_rect.left_upper_coords.GetX() -
          our_rect.right_lower_coords.GetX() > constants::kEpsilon ||
          our_rect.left_upper_coords.GetX() -
              other_rect.right_lower_coords.GetX() > constants::kEpsilon);

  bool is_intersected_along_y_axis =
      !(other_rect.left_upper_coords.GetY() -
          our_rect.right_lower_coords.GetY() > constants::kEpsilon ||
          our_rect.left_upper_coords.GetY() -
              other_rect.right_lower_coords.GetY() > constants::kEpsilon);

  return (is_intersected_along_x_axis && is_intersected_along_y_axis);
}

HitBox::Rect HitBox::GetRect() const {
  Point left_upper_coords(pos_.GetX() - hit_box_width_ / 2,
                          pos_.GetY() - hit_box_height_ / 2 +
                              vertical_shift_);
  Point right_lower_coords(pos_.GetX() + hit_box_width_ / 2,
                           pos_.GetY() + hit_box_height_ / 2
                               + vertical_shift_);

  return Rect(left_upper_coords, right_lower_coords);
}
