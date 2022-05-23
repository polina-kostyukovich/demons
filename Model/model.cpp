#include "model.h"

const Hero& Model::GetHero() const {
  return hero_;
}

Hero& Model::GetHero() {
  return hero_;
}

const Map& Model::GetMap() const {
  return map_;
}

Map& Model::GetMap() {
  return map_;
}

const NpcController& Model::GetNpcController() const {
  return npc_controller_;
}

NpcController& Model::GetNpcController() {
  return npc_controller_;
}

void Model::LoadPictures() {
  hero_.LoadPictures();
  map_.LoadPictures();
  Fireball::LoadPictures();
  Npc::LoadPictures();
}

std::vector<Fireball>& Model::GetFireballs() {
  return fireballs_;
}

const std::vector<Fireball>& Model::GetFireballs() const {
  return fireballs_;
}

void Model::AddFireball(const Fireball& fireball) {
  fireballs_.emplace_back(fireball);
}

std::vector<GameObject*> Model::GetAllGameObjects() {
  std::vector<GameObject*> result;
  for (const auto& object : GetMap().GetObjects()) {
    result.emplace_back(object.get());
  }
  for (auto& object : GetFireballs()) {
    result.emplace_back(&object);
  }

  for (auto& object : GetNpcController().GetNpcList()) {
    result.emplace_back(&object);
  }

  result.emplace_back(&GetHero());

  return result;
}
