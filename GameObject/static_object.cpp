#include "static_object.h"

StaticObject::StaticObject(const Point& position) :
    GameObject(position), top_hit_box_(position_) {}

const HitBox& StaticObject::GetTopHitBox() const {
  return top_hit_box_;
}

void StaticObject::SetIsOverHero(bool is_over_hero) {
  is_over_hero_ = is_over_hero;
}
bool StaticObject::IsOverHero() const {
  return is_over_hero_;
}
