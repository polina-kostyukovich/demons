#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include <memory>
#include <QPainter>
#include "creature.h"
// #include "../Animation/animation.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point());
  void LoadPictures();

  void Move(const Vector2D& direction, int window_width, int window_height);

  Animation GetAnimation(int counter) const;
 private:
  std::vector<QPixmap> wings_pixmaps;
  std::vector<QPixmap> hero_pixmaps;
};

#endif  // GAMEOBJECT_HERO_H_
