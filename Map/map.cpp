#include "map.h"

Map::Map(int window_width, int window_height) {
  columns_ = (window_width - 1) / constants::kObjectSize + 1;
  rows_ = (window_height - 1) / constants::kObjectSize + 1;
  objects_ = std::vector<std::vector<GameObject*>>(
      columns_, std::vector<GameObject*>(rows_, nullptr));
}

void Map::SetObject(GameObject* object, int x, int y) {
  objects_[x][y] = object;
}

const GameObject* Map::GetObject(int x, int y) const {
  return objects_[x][y];
}
