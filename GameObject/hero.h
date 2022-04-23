#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include "creature.h"
#include "../Util/vector.h"
#include "../Animation/animation.h"
#include <QPainter>

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point());

  void Move(const Vector2D& direction, int window_width, int window_height);

  void DrawHero(QPainter* painter, const Point& hero_pos, int size,
                Animation& animation) const;
  void DrawWings(QPainter* painter, const Point& hero_pos, int size,
                 int counter, Animation* animation) const;
};

#endif  // GAMEOBJECT_HERO_H_
