#ifndef ANIMATION_WINGS_H_
#define ANIMATION_WINGS_H_

#include "../Util/point.h"
#include <QPainter>

class Wings {
 public:
  Wings();
  void DrawWings(QPainter* painter, const Point& hero_pos, int size,
                 int counter);
 private:
  std::vector<QPixmap> wings_pixmaps;
};

#endif  // ANIMATION_WINGS_H_
