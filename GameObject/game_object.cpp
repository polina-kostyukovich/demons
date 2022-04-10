#include "game_object.h"

GameObject::GameObject(const Point& position) : position_(position) {}

void GameObject::SetPosition(const Point& new_position) {
  position_ = new_position;
}

Point GameObject::GetPosition() const {
  return position_;
}
