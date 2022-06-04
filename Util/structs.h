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
  kMenuMusic = 0,
  kBackgroundMusic = 1,
  kNpcAppearance = 2,
  kNpcHit = 3,
  kHeroShot = 4,
  kVictoryMusic = 5,
  kDefeatMusic = 6,
};

#endif  // UTIL_STRUCTS_H_
