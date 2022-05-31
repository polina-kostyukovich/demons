#ifndef CONTROLLER_NPC_CONTROLLER_H_
#define CONTROLLER_NPC_CONTROLLER_H_

#include <vector>

#include "../GameObject/boiler.h"
#include "../GameObject/npc.h"

class NpcController {
 public:
  NpcController();
  void Update(const Point& hero_position);

  const std::vector<Npc>& GetNpcList() const;
  std::vector<Npc>& GetNpcList();

  std::vector<Point> GetNpcCoordinates() const;

  void ClearNpcList();

  void IncrementTickCounter();

  bool NeedToCreateNpc() const;

  void CreateNpc(const Point& hero_pos,
                 std::vector<Point>&& boilers_coords,
                 int boiler_height);

 private:
  std::vector<Npc> npc_list_;
  int tick_counter_{-1};
};

#endif  // CONTROLLER_NPC_CONTROLLER_H_
