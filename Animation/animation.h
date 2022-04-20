#ifndef ANIMATION_H_
#define ANIMATION_H_

#include <QPainter>

class Animation {
 public:
  Animation();
  std::vector<QPixmap> hero_pixmaps;
  std::vector<QPixmap> wings_pixmaps;
  QPixmap lava;
  QPixmap horizontal_wall;
  QPixmap vertical_wall;
};

#endif  // ANIMATION_H_
