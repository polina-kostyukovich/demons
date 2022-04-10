#include "game_object.h"

GameObject::GameObject(const Point& point) : position_(point) {}

void GameObject::SetPosition(const Point& new_point) {
  position_ = new_point;
}

Point GameObject::GetPosition() const {
  return position_;
}
