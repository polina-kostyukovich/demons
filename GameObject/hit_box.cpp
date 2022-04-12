#include "hit_box.h"

Rect HitBox::GetRect() const {
}

bool HitBox::IsCollided(const Rect& other_rect) const {
}

bool HitBox::IsCollided(const HitBox& other_hit_box) const {
}

HitBox::HitBox(const Point* pos, double width, double height) {
  pos_ = std::make_unique<Point>(pos);
  width_ = width;
  height_ = height;
}
