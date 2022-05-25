#ifndef GAMEOBJECT_FIREBALL_H_
#define GAMEOBJECT_FIREBALL_H_

#include <vector>

#include "dynamic_object.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Fireball : public DynamicObject {
 public:
  Fireball(const Point& position, const Point& purpose);

  static void LoadPictures();
  Picture GetPicture() const override;

  void Move(const Point& spawn_pos);

  bool IsBorn();
  void SetBorn(bool is_born);

  int GetCounter();
  void SetCounter(int count);

  void CreateDirection();

  Point GetPurpose() const;

 private:
  Vector2D direction_;
  Point purpose_;
  static inline std::vector<QPixmap> pictures_;
  bool is_born_{true};
  int tick_counter_{0};
};

#endif  // GAMEOBJECT_FIREBALL_H_
