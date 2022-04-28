#ifndef UTIL_STRUCTS_H_
#define UTIL_STRUCTS_H_

#include <QPixmap>
#include "point.h"

struct Picture {
  QPixmap picture;
  Point left_top;
  int width;
  int height;
};

#endif  // UTIL_STRUCTS_H_
