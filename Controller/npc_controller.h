#ifndef CONTROLLER_NPC_CONTROLLER_H_
#define CONTROLLER_NPC_CONTROLLER_H_

#include <vector>

#include "../GameObject/npc.h"

class NpcController {
 public:
  NpcController();
  void Update(const Point& hero_position);

 private:
  std::vector<Npc> npc_list_;
};

#endif  // CONTROLLER_NPC_CONTROLLER_H_
