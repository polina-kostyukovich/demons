#ifndef CONTROLLER_NPC_CONTROLLER_H_
#define CONTROLLER_NPC_CONTROLLER_H_

#include <vector>

#include "../GameObject/npc.h"
#include "../Map/map.h"

class NpcController {
 public:
  NpcController();
  void Update(const Point& hero_position, const Map& map);

  const std::vector<Npc>& GetNpcList() const;

 private:
  std::vector<Npc> npc_list_;
};

#endif  // CONTROLLER_NPC_CONTROLLER_H_
