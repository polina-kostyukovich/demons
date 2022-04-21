#include "animation.h"
#include <string>

Animation::Animation() {
  Q_INIT_RESOURCE(resources);
  // static objects
  lava = QPixmap(":Picture/StaticObject/lava.png");
  horizontal_wall = QPixmap(":Picture/StaticObject/horizontal_wall.png");
  vertical_wall = QPixmap(":Picture/StaticObject/vertical_wall.png");
  // animation objects
  MakeHero();
  MakeWings();
}

void Animation::MakeHero() {
  std::string str = ":Picture/Hero/demonessa";
  for (int i = 0; i <= 6; i++) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
  for (int i = 5; i >= 0; i--) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
}

void Animation::MakeWings() {
  std::string str = ":Picture/Wings/wings";
  for (int i = 0; i <= 6; i++) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
  for (int i = 5; i >= 0; i--) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
}
