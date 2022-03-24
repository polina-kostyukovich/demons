#include "map.h"

Map::Map(int window_width, int window_height) {
  columns_ = (window_width - 1) / constants::kObjectSize + 1;
  rows_ = (window_height - 1) / constants::kObjectSize + 1;
  objects_.resize(columns_);
  for (auto &column : objects_) {
    column.resize(rows_);
  }
}

void Map::SetObject(std::unique_ptr<GameObject>&& object, int x, int y) {
  objects_[x][y] = std::move(object);
}

const std::unique_ptr<GameObject>& Map::GetObject(int x, int y) const {
  return objects_[x][y];
}
