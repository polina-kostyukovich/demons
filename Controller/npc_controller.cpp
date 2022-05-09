#include "npc_controller.h"

NpcController::NpcController() {}

void NpcController::Update(const Point& hero_position) {
  for (auto& npc : npc_list_) {
    npc.Update(hero_position);
  }
}
