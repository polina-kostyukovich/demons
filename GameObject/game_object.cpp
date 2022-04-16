#include "game_object.h"

GameObject::GameObject(const Point& position) : position_(position) {}

void GameObject::SetPosition(const Point& new_position) {
  position_ = new_position;
}

Point GameObject::GetPosition() const {
  return position_;
}

void GameObject::SetPositionX(long double new_x) {
  position_.SetX(new_x);
}

void GameObject::SetPositionY(long double new_y) {
  position_.SetY(new_y);
}
