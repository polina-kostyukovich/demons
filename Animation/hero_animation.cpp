#include "hero_animation.h"

HeroAnimation::HeroAnimation() {
  std::string str = ":Picture/Hero/demonessa";
  for (int i = 0; i < constants::kMiddleAnimation; i++) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
  for (int i = constants::kMiddleAnimation; i > 0; i--) {
    str += std::to_string(i);
    str += ".png";
    hero_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
}

void HeroAnimation::DrawHero(QPainter* painter, const Point& hero_pos,
                             int size) {
  painter->drawPixmap(static_cast<int> (hero_pos.GetX()),
                      static_cast<int>(hero_pos.GetY()), size, size,
                      hero_pixmaps[0]);
}
