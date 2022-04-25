#include "animation.h"
#include <string>

Animation::Animation() {
  Q_INIT_RESOURCE(resources);
  lava = QPixmap(":Resources/Picture/StaticObject/lava.png");
  horizontal_wall =
      QPixmap(":Resources/Picture/StaticObject/horizontal_wall.png");
  vertical_wall = QPixmap(":Resources/Picture/StaticObject/vertical_wall.png");

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
    hero_pixmaps.emplace_back(QPixmap(file_demonessa.c_str()));
    wings_pixmaps.emplace_back(QPixmap(file_wings.c_str()));
  }
}

void Animation::SetCounter(int i) {
  counter_ = i;
}

int Animation::GetCounter() {
  return counter_;
}
