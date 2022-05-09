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

const NpcController &Model::GetNpcController() const {
  return npc_controller_;
}

NpcController &Model::GetNpcController() {
  return npc_controller_;
}

void Model::LoadPictures() {
  hero_.LoadPictures();
  map_.LoadPictures();
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