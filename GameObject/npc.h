#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include <string>
#include <vector>

#include "creature.h"
#include "../Util/structs.h"
#include "../Util/vector.h"
#include "hero.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position = Point());

  static void LoadPictures();

  void Update(const Point& target_position);
  void Move(const Vector2D& direction);

  Picture GetPicture() const;

  int GetCounter() const;
  void SetCounter(int counter);

  bool IsAttacking() const;
  void SetAttackingStatus(bool is_attacking);

  int GetAttackTickCounter() const;
  void SetAttackTickCounter(int counter);
  void IncrementAttackTickCounter();

  void AttackHero(Hero* hero);

 private:
  static void InputPictures(std::string);

 private:
  static inline std::vector<QPixmap> pictures_;
  bool is_moving_right_;
  int tick_counter_{0};

  bool is_attacking_{false};
  int attack_tick_counter_{-1};
};

#endif  // GAMEOBJECT_NPC_H_
