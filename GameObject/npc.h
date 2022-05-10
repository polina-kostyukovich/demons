#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include "creature.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position = Point());

  static void LoadPictures();

  void Update(const Point& target_position);
  void Move(const Vector2D& direction);

  Picture GetPicture() const;

  int GetCounter();
  void SetCounter(int counter);

 private:
  static void InputPictures(std::string);

 private:
  static inline std::vector<QPixmap> pictures_;
  bool is_move_right_;
  int tick_counter_{0};
};

#endif  // GAMEOBJECT_NPC_H_
