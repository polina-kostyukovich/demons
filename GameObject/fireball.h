#ifndef GAMEOBJECT_FIREBALL_H_
#define GAMEOBJECT_FIREBALL_H_

#include <vector>

#include "dynamic_object.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Fireball : public DynamicObject {
 public:
  Fireball(const Point& position, const Vector2D& direction) :
      DynamicObject(position), direction_(direction) {}

  static void LoadPictures();
  Picture GetPicture() const;

  void Move();

  bool IsBorn();
  void SetBorn(bool set);

  int GetCounter();
  void SetCounter(int count);

  void SetSpawnPos(const Point& pos);

 private:
  Vector2D direction_;
  static inline std::vector<QPixmap> pictures_;
  bool is_born_{true};
  int tick_counter_{0};
  Point spawn_pos_;
};

#endif  // GAMEOBJECT_FIREBALL_H_
