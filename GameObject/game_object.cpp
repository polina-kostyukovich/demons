#include "game_object.h"

GameObject::GameObject(const Point& position) :
    position_(position), hit_box_(position_) {}

GameObject::GameObject(const GameObject& other_object) :
    position_(other_object.GetPosition()), hit_box_(position_) {
  hit_box_.SetVerticalShift(other_object.hit_box_.GetVerticalShift());
  hit_box_.SetHeight(other_object.hit_box_.GetHeight());
  hit_box_.SetWidth(other_object.hit_box_.GetWidth());
}

GameObject::GameObject(GameObject&& other_object) :
    position_(other_object.GetPosition()), hit_box_(position_) {
  hit_box_.SetVerticalShift(other_object.hit_box_.GetVerticalShift());
  hit_box_.SetHeight(other_object.hit_box_.GetHeight());
  hit_box_.SetWidth(other_object.hit_box_.GetWidth());
}

GameObject& GameObject::operator=(const GameObject& other_object) {
  position_ = other_object.GetPosition();
  hit_box_.SetVerticalShift(other_object.hit_box_.GetVerticalShift());
  hit_box_.SetWidth(other_object.hit_box_.GetWidth());
  hit_box_.SetHeight(other_object.hit_box_.GetHeight());
  return *this;
}

GameObject& GameObject::operator=(GameObject&& other_object) {
  position_ = other_object.GetPosition();
  hit_box_.SetVerticalShift(other_object.hit_box_.GetVerticalShift());
  hit_box_.SetWidth(other_object.hit_box_.GetWidth());
  hit_box_.SetHeight(other_object.hit_box_.GetHeight());
  return *this;
}

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

const HitBox& GameObject::GetHitBox() const {
  return hit_box_;
}
