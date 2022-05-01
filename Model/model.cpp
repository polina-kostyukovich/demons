#include "model.h"

Hero& Model::GetHero() {
  return hero_;
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

std::vector<Fireball> Model::GetFireballs() const {
  return fireballs_;
}

void Model::AddFireball(const Fireball& fireball) {
  fireballs_.emplace_back(fireball);
}

std::pair<int, int> Model::GetCellSize(int window_width,
                                       int window_height) const {
  int width = window_width / map_.GetColumnsNumber();
  int height = window_height / map_.GetRowsNumber();
  return {width, height};
}
std::pair<int, int> Model::GetCellCoordinatesOnMap(const Point& point,
                                                   int window_width,
                                                   int window_height) const {
  auto cell = GetCellSize(window_width, window_height);
  int x = static_cast<int>(point.GetX() / cell.first);
  int y = static_cast<int>(point.GetY() / cell.second);
  return {x, y};
}
