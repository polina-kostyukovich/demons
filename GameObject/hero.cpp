#include "hero.h"

Hero::Hero(const Point& position) : Creature(position) {}

void Hero::Move(const Vector2D& direction,
                int window_width,
                int window_height) {
  SetPosition(GetPosition() + direction * constants::kHeroStep);

  if (GetPosition().GetX() < -constants::kEpsilon) {
    SetPositionX(0);
  }
  if (GetPosition().GetX() > constants::kEpsilon + window_width) {
    SetPositionX(static_cast<long double>(window_width));
  }
  if (GetPosition().GetY() < -constants::kEpsilon) {
    SetPositionY(0);
  }
  if (GetPosition().GetY() > constants::kEpsilon + window_height) {
    SetPositionY(static_cast<long double>(window_height));
  }
}
