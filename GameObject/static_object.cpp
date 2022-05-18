#include "static_object.h"

StaticObject::StaticObject(const Point& position) :
    GameObject(position), picture_above_hit_box_(position_) {}

const HitBox& StaticObject::GetTopHitBox() const {
  return picture_above_hit_box_;
}

void StaticObject::SetIsOverSomething(bool is_over_hero) {
  is_over_something = is_over_hero;
}

bool StaticObject::IsOverSomething() const {
  return is_over_something;
}
