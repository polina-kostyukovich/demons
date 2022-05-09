#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include <memory>
#include <vector>
#include <QPainter>

#include "creature.h"
#include "../Map/map.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point());
  void LoadPictures();

  void Move(const Vector2D& direction, int window_width, int window_height);

  Picture GetPicture(int counter) const;

 private:
  std::vector<QPixmap> wings_pixmaps_;
  std::vector<QPixmap> hero_pixmaps_;
};

#endif  // GAMEOBJECT_HERO_H_
