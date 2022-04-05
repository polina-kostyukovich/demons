#include "game_object.h"

GameObject::GameObject(const Point& point) : point_(point) {}

void GameObject::SetPoint(const Point& new_point) {
  point_ = new_point;
}

Point GameObject::GetPoint() const {
  return point_;
}
