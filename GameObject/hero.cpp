#include "hero.h"

#include <iostream>
#include <string>

Hero::Hero(const Point& position) : Creature(position) {}

void Hero::LoadPictures() {
  int reverse;
  for (int i = 1; i <= constants::kNumberAnimation; i++) {
    std::string file_demonessa = ":Resources/Picture/Hero/demonessa";
    std::string file_wings = ":Resources/Picture/Wings/wings";
    if (i <= constants::kMiddleAnimation) {
      file_demonessa += std::to_string(i);
      file_wings += std::to_string(i);
    } else {
      reverse = 2 * constants::kMiddleAnimation - i;
      file_demonessa += std::to_string(reverse);
      file_wings += std::to_string(reverse);
    }
    file_demonessa += ".png";
    file_wings += ".png";
    hero_pixmaps_.emplace_back(QPixmap(file_demonessa.c_str()));
    wings_pixmaps_.emplace_back(QPixmap(file_wings.c_str()));
  }
}

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

Picture Hero::GetPicture(int counter) const {
  Picture output;
  output.left_top = position_;
  output.width = constants::kHeroSize;
  output.height = constants::kHeroSize;
  QPixmap pixmap(wings_pixmaps_[counter / constants::kHeroSpeedCoefficient]);
  QPainter painter(&pixmap);

  QPixmap hero_image(hero_pixmaps_[number_tick_
      / constants::kHeroSpeedCoefficient].scaled(
      pixmap.width(),
      pixmap.height()));

  painter.drawPixmap(0, 0, hero_image);
  output.picture = pixmap;
  return output;
}

int Hero::GetNumberTick() {
  return number_tick_;
}

void Hero::SetNumberTick(int number) {
  number_tick_ = number;
}

bool Hero::IsStriking() {
  return is_striking_;
}

void Hero::SetStriking(bool is_striking) {
  is_striking_ = is_striking;
}
