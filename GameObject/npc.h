#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include "creature.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position = Point());

 private:

};

#endif  // GAMEOBJECT_NPC_H_
