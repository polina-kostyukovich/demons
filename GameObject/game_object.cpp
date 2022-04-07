#include "game_object.h"

GameObject::GameObject(const Point& point) : position_(point) {}

void GameObject::SetPoint(const Point& new_point) {
  position_ = new_point;
}

Point GameObject::GetPoint() const {
  return position_;
}
