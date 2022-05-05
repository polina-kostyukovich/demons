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
                int window_height,
                const Map& map) {
  int width = window_width - constants::kHeroSize;
  int height = window_height - constants::kHeroSize;
  Point old_position = position_;
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

  Point moved_pos_x =
      Point(position_.GetX(), old_position.GetY() + constants::kHeroSize / 2.);
  auto x_left_top_map_coord = map.GetCellCoordinatesOnMap(moved_pos_x);
  auto x_left_bottom_map_coord = map.GetCellCoordinatesOnMap(
      moved_pos_x + Point(0., constants::kHeroSize / 2.));
  auto x_right_top_map_coord = map.GetCellCoordinatesOnMap(
      moved_pos_x + Point(constants::kHeroSize, 0.));

  if (direction.GetX() <= -constants::kEpsilon) {
    for (int map_y = x_left_top_map_coord.second;
         map_y <= x_left_bottom_map_coord.second; ++map_y) {
      if (map.GetObject(x_left_top_map_coord.first, map_y) != nullptr) {
        position_.SetX(old_position.GetX());
        break;
      }
    }
  } else if (direction.GetX() >= constants::kEpsilon) {
    for (int map_y = x_left_top_map_coord.second;
         map_y <= x_left_bottom_map_coord.second; ++map_y) {
      if (map.GetObject(x_right_top_map_coord.first, map_y) != nullptr) {
        position_.SetX(old_position.GetX());
        break;
      }
    }
  }

  Point moved_pos_y =
      Point(old_position.GetX(), position_.GetY() + constants::kHeroSize / 2.);
  auto y_left_top_map_coord = map.GetCellCoordinatesOnMap(moved_pos_y);
  auto y_left_bottom_map_coord = map.GetCellCoordinatesOnMap(
      moved_pos_y + Point(0., constants::kHeroSize / 2.));
  auto y_right_top_map_coord = map.GetCellCoordinatesOnMap(
      moved_pos_y + Point(constants::kHeroSize, 0.));

  if (direction.GetY() <= -constants::kEpsilon) {
    for (int map_x = y_left_top_map_coord.first;
         map_x <= y_right_top_map_coord.first; ++map_x) {
      if (map.GetObject(map_x, y_left_top_map_coord.second) != nullptr) {
        position_.SetY(old_position.GetY());
        break;
      }
    }
  } else if (direction.GetY() >= constants::kEpsilon) {
    for (int map_x = y_left_top_map_coord.first;
         map_x <= y_right_top_map_coord.first; ++map_x) {
      if (map.GetObject(map_x, y_left_bottom_map_coord.second) != nullptr) {
        position_.SetY(old_position.GetY());
        break;
      }
    }
  }

  // std::clog << "after: " << position_ << '\n';
}

Picture Hero::GetPicture(int counter) const {
  Picture output;
  output.left_top = position_;
  output.width = constants::kHeroSize;
  output.height = constants::kHeroSize;
  QPixmap pixmap(wings_pixmaps_[counter / constants::kSlowAnimation]);
  QPainter painter(&pixmap);

  QPixmap hero_image(hero_pixmaps_[0].scaled(pixmap.width(), pixmap.height()));

  painter.drawPixmap(0, 0, hero_image);
  output.picture = pixmap;
  return output;
}
