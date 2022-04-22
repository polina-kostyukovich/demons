#ifndef ANIMATION_HERO_ANIMATION_H_
#define ANIMATION_HERO_ANIMATION_H_

#include "../Util/point.h"
#include <QPainter>

class HeroAnimation {
 public:
  HeroAnimation();
  void DrawHero(QPainter* painter, const Point& hero_pos, int size);
 private:
  std::vector<QPixmap> hero_pixmaps;
};

#endif  // ANIMATION_HERO_ANIMATION_H_
