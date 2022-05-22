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

enum class Language {
  kEnglish,
  kRussian,
};

enum class Sound {
  kMenuMusic,
  kBackgroundMusic,
  kNpcAppearance,
  kNpcHit,
  kHeroShot
};

#endif  // UTIL_STRUCTS_H_
