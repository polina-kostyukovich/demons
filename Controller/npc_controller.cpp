#include "npc_controller.h"

#include <random>

NpcController::NpcController() {
  npc_list_.push_back(Npc(Point(800, 800)));
  npc_list_.push_back(Npc(Point(600, 600)));
  npc_list_.push_back(Npc(Point(100, 300)));
  npc_list_.push_back(Npc(Point(1000, 1000)));
  npc_list_.push_back(Npc(Point(800, 100)));
  // todo from boilers
}

void NpcController::Update(const Point& hero_position) {
  for (auto& npc: npc_list_) {
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

void NpcController::CreateNpc(const Point& hero_pos,
                              std::vector<Point>&& boilers_coords,
                              int boiler_height) {
  std::shuffle(boilers_coords.begin(),
               boilers_coords.end(),
               std::mt19937(std::random_device()()));
  Point npc_pos = boilers_coords[0] +
      Point(0, (constants::kNpcSize - boiler_height) / 2.);
  npc_list_.emplace_back(npc_pos, boiler_height);
}
