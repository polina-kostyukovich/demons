#ifndef ANIMATION_ANIMATION_H_
#define ANIMATION_ANIMATION_H_

#include <QPainter>
#include <vector>

#include "wings.h"
#include "hero_animation.h"

class Animation {
 public:
  Animation();
  void SetCounter(int i);
  int GetCounter();

 public:
  QPixmap lava;
  QPixmap horizontal_wall;
  QPixmap vertical_wall;
  int counter_{0};
  Wings wings_;
  HeroAnimation hero_animation_;
};

#endif  // ANIMATION_ANIMATION_H_
