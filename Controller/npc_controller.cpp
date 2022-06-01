#include "npc_controller.h"

#include <algorithm>
#include <memory>
#include <random>

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

std::vector<Npc>& NpcController::GetNpcList() {
  return npc_list_;
}

std::vector<Point> NpcController::GetNpcCoordinates() const {
  std::vector<Point> result(npc_list_.size());
  for (int i = 0; i < npc_list_.size(); ++i) {
    result[i] = npc_list_[i].GetPosition();
  }

  return result;
}

void NpcController::ClearNpcList() {
  npc_list_.clear();
  tick_counter_ = -1;
}

void NpcController::IncrementTickCounter() {
  ++tick_counter_;
  tick_counter_ %= constants::kTicksBetweenNpcAppearance;
}

bool NpcController::NeedToCreateNpc() const {
  return tick_counter_ == 0;
}

void NpcController::CreateNpc(const Point& hero_pos, const Map& map) {
  auto boilers_coords = map.GetBoilersCoords();
  std::shuffle(boilers_coords.begin(),
               boilers_coords.end(),
               std::mt19937(std::random_device()()));

  Point boiler_pos;
  if (npc_list_.empty() ||
      boilers_coords[0] != npc_list_.back().GetSpawnPos() ||
      boilers_coords.size() == 1) {
    boiler_pos = boilers_coords[0];
  } else {
    boiler_pos = boilers_coords[1];
  }

  auto& static_objects = map.GetObjects();
  auto our_boiler = std::find_if(static_objects.begin(),
                                 static_objects.end(),
                                 [&boiler_pos](auto object) {
    return object->GetPosition() == boiler_pos;
  });

  Point npc_pos = boiler_pos +
      Point(0.,
            (*our_boiler)->GetHitBox().GetVerticalShift()
               - (*our_boiler)->GetHitBox().GetHeight() / 2
               - constants::kNpcSize * constants::kNpcHitBoxHeightCoefficient
               + constants::kNpcSize / 2);

  npc_list_.emplace_back(npc_pos, std::weak_ptr<StaticObject>(*our_boiler));
}
