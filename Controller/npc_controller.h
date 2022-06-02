#ifndef CONTROLLER_NPC_CONTROLLER_H_
#define CONTROLLER_NPC_CONTROLLER_H_

#include <vector>

#include "../GameObject/npc.h"
#include "../Map/map.h"

class NpcController {
 public:
  NpcController() = default;
  void Update(const Point& hero_position, const Map& map);

  const std::vector<Npc>& GetNpcList() const;
  std::vector<Npc>& GetNpcList();

  std::vector<Point> GetNpcCoordinates() const;

  void ClearNpcList();

  void IncrementTickCounter();

  bool NeedToCreateNpc() const;

  void CreateNpc(const Point& hero_pos, const Map& map);



 private:
  std::vector<Npc> npc_list_;
  int tick_counter_{-1};
};

#endif  // CONTROLLER_NPC_CONTROLLER_H_
