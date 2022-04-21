#ifndef ANIMATION_ANIMATION_H_
#define ANIMATION_ANIMATION_H_

#include <QPainter>
#include <vector>

class Animation {
 public:
  Animation();
  std::vector<QPixmap> hero_pixmaps;
  std::vector<QPixmap> wings_pixmaps;
  QPixmap lava;
  QPixmap horizontal_wall;
  QPixmap vertical_wall;

  int counter_{0};
 private:
  void MakeHero();
  void MakeWings();
};

#endif  // ANIMATION_ANIMATION_H_
