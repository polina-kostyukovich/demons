#include "npc_controller.h"

NpcController::NpcController() {
  npc_list_.push_back(Npc(Point(800, 800)));
  npc_list_.push_back(Npc(Point(800, 100)));  // for test
  // todo from boilers
}

void NpcController::Update(const Point& hero_position) {
  for (auto& npc : npc_list_) {
    npc.Update(hero_position);
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

std::vector<Npc> &NpcController::GetNpcList() {
  return npc_list_;
}

std::vector<Npc*> NpcController::GetNpcs() {
  std::vector<Npc*> npcs;
  for (auto& npc : npc_list_) {
    npcs.push_back(&npc);
  }

  return npcs;
}

std::vector<Point> NpcController::GetNpcCoordinates() const {
  std::vector<Point> result;
  for (const auto& npc : npc_list_) {
    result.push_back(npc.GetPosition());
  }

  return result;
}
