#include "npc_controller.h"

NpcController::NpcController() {
  npc_list_.push_back(Npc(Point(800, 800)));
  npc_list_.push_back(Npc(Point(0, 0)));  // for test
  // todo from boilers
}

void NpcController::Update(const Point& hero_position, Map& map) {
  for (auto& npc : npc_list_) {
    npc.Update(hero_position, map);
    if (npc.GetCounter() + 1 == constants::kNumberOfNpc *
        constants::kNpcSpeedCoefficient) {
      npc.SetCounter(0);
    } else {
      npc.SetCounter(npc.GetCounter() + 1);
    }
  }
}

const std::vector<Npc>& NpcController::GetNpcList() const {
  return npc_list_;
}
