#include "animation.h"

Animation::Animation() {
  Q_INIT_RESOURCE(resources);
  lava = QPixmap(":Picture/StaticObject/lava.png");
  horizontal_wall = QPixmap(":Picture/StaticObject/horizontal_wall.png");
  vertical_wall = QPixmap(":Picture/StaticObject/vertical_wall.png");
}

int Animation::GetCounter() {
  return counter_;
}

void Animation::SetCounter(int i) {
  counter_ = i;
}
