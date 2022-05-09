#include "npc_controller.h"

NpcController::NpcController() {
  npc_list_.push_back(Npc(Point(800, 800)));
  npc_list_.push_back(Npc(Point(0, 0))); // for test
}

void NpcController::Update(const Point& hero_position) {
  for (auto& npc : npc_list_) {
    npc.Update(hero_position);
  }
}

const std::vector<Npc> &NpcController::GetNpcList() const {
  return npc_list_;
}
