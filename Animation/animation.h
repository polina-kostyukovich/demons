#ifndef ANIMATION_ANIMATION_H_
#define ANIMATION_ANIMATION_H_

#include <QPainter>
#include <vector>
#include "../Model/constants.h"

class Animation {
 public:
  Animation();
  void SetCounter(int i);
  int GetCounter();

 public:
  QPixmap lava;
  QPixmap horizontal_wall;
  QPixmap vertical_wall;
  std::vector<QPixmap> wings_pixmaps;
  std::vector<QPixmap> hero_pixmaps;

 private:
  int counter_{0};
};

#endif  // ANIMATION_ANIMATION_H_
