#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include <memory>
#include <QPainter>
#include "creature.h"
#include "../Animation/animation.h"
#include "../Util/vector.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point());

  void Move(const Vector2D& direction, int window_width, int window_height);

  void DrawHero(QPainter* painter, int size,
                const Animation& animation) const;
  void DrawWings(QPainter* painter, int size, int counter,
                 const Animation& animation) const;
};

#endif  // GAMEOBJECT_HERO_H_
