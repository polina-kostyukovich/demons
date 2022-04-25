#include "hero.h"

#include <iostream>

Hero::Hero(const Point& position) : Creature(position) {}

void Hero::Move(const Vector2D& direction,
                int window_width,
                int window_height) {
  int width = window_width - constants::kHeroSize;
  int height = window_height - constants::kHeroSize;
  SetPosition(GetPosition() + direction * constants::kHeroStep);
  // std::clog << "Coords depending on checking collisions: before: "
  //           << position_ << "; ";

  if (GetPosition().GetX() < -constants::kEpsilon) {
    SetPositionX(0.);
  }
  if (GetPosition().GetX() > constants::kEpsilon + width) {
    SetPositionX(static_cast<long double>(width));
  }
  if (GetPosition().GetY() < -constants::kEpsilon) {
    SetPositionY(0.);
  }
  if (GetPosition().GetY() > constants::kEpsilon + height) {
    SetPositionY(static_cast<long double>(height));
  }

  // std::clog << "after: " << position_ << '\n';
}

void Hero::DrawHero(QPainter* painter, int size,
                    const Animation& animation) const {
  painter->drawPixmap(static_cast<int> (GetPosition().GetX()),
                      static_cast<int>(GetPosition().GetY()), size, size,
                      animation.hero_pixmaps[0]);
}

void Hero::DrawWings(QPainter* painter, int size, int counter,
                     const Animation& animation) const {
  painter->drawPixmap(static_cast<int> (GetPosition().GetX()),
                      static_cast<int>(GetPosition().GetY()), size, size,
                      animation.wings_pixmaps[counter
                          / constants::kSlowAnimation]);
}
