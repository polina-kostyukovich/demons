#include "wings.h"

void Wings::DrawWings(QPainter* painter, const Point& hero_pos, int size,
                      int counter) {
  painter->drawPixmap(static_cast<int> (hero_pos.GetX()),
                      static_cast<int>(hero_pos.GetY()), size, size,
                      wings_pixmaps[counter / constants::kSlowAnimation]);
}

Wings::Wings() {
  std::string str = ":Picture/Wings/wings";
  for (int i = 0; i < constants::kMiddleAnimation; i++) {
    str += std::to_string(i);
    str += ".png";
    wings_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
  for (int i = constants::kMiddleAnimation; i > 0; i--) {
    str += std::to_string(i);
    str += ".png";
    wings_pixmaps.emplace_back(QPixmap(str.c_str()));
  }
}
