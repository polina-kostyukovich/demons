#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include <string>
#include <vector>

#include "creature.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position, int boiler_height);

  static void LoadPictures();

  void Update(const Point& target_position);
  void Move(const Vector2D& direction);

  Picture GetPicture() const;

  int GetCounter() const;
  void SetCounter(int counter);

 private:
  static void InputPictures(std::string);

  void UpdateFieldsIfBorn(const Point& target_position);

 private:
  static inline std::vector<QPixmap> pictures_;
  bool is_moving_right_;
  int tick_counter_{0};
  Point spawn_pos_;
  bool is_born_{true};
  int boiler_height_;
};

#endif  // GAMEOBJECT_NPC_H_
