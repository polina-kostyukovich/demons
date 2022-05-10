#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include "creature.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position = Point());

  void Update(const Point& target_position);
  void Move(const Vector2D& direction);
};

#endif  // GAMEOBJECT_NPC_H_
