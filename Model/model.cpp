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

void Model::LoadPictures() {
  hero_.LoadPictures();
  map_.LoadPictures();
  Fireball::LoadPictures();
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
