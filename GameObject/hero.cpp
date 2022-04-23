#include "hero.h"

#include <iostream>

Hero::Hero(const Point& position) : Creature(position) {}

void Hero::Move(const Vector2D& direction,
                int window_width,
                int window_height) {
  SetPosition(GetPosition() + direction * constants::kHeroStep);

  // std::clog << "Coords depending on checking collisions: before: "
  //           << position_ << "; ";

  if (GetPosition().GetX() < -constants::kEpsilon) {
    SetPositionX(0.);
  }
  if (GetPosition().GetX() > constants::kEpsilon + window_width) {
    SetPositionX(static_cast<long double>(window_width));
  }
  if (GetPosition().GetY() < -constants::kEpsilon) {
    SetPositionY(0.);
  }
  if (GetPosition().GetY() > constants::kEpsilon + window_height) {
    SetPositionY(static_cast<long double>(window_height));
  }

  // std::clog << "after: " << position_ << '\n';
}

void Hero::DrawHero(QPainter* painter,
                    const Point& hero_pos,
                    int size,
                    Animation *animation) const {
  painter->drawPixmap(static_cast<int> (hero_pos.GetX()),
                      static_cast<int>(hero_pos.GetY()), size, size,
                      animation->hero_pixmaps[0]);
}

void Hero::DrawWings(QPainter* painter,
                     const Point& hero_pos,
                     int size,
                     int counter, Animation* animation) const {
  painter->drawPixmap(static_cast<int> (hero_pos.GetX()),
                      static_cast<int>(hero_pos.GetY()), size, size,
                      animation->wings_pixmaps[counter
                          / constants::kSlowAnimation]);
}
