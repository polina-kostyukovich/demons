#ifndef GAMEOBJECT_HERO_H_
#define GAMEOBJECT_HERO_H_

#include <memory>
#include <vector>
#include <QPainter>

#include "creature.h"
#include "../Map/map.h"
#include "../Model/constants.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Hero : public Creature {
 public:
  explicit Hero(const Point& position = Point(constants::kHeroSize / 2.,
                                              constants::kHeroSize / 2.));
  void LoadPictures();

  void Move(const Vector2D& direction, int window_width, int window_height);

  Picture GetPicture(int counter) const;

  Picture GetPicture() const override;

  int GetNumberTick();
  void SetNumberTick(int number);
  bool IsStriking();
  void SetStrikingStatus(bool is_striking);

  int GetStandingTicks() const;
  void SetStandingTicks(int ticks);
  void IncrementStandingTicks();

 private:
  std::vector<QPixmap> wings_pixmaps_;
  std::vector<QPixmap> hero_pixmaps_;
  int number_tick_{0};
  bool is_striking_{false};
  int standing_ticks_{0};
};

#endif  // GAMEOBJECT_HERO_H_
