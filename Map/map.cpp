#include "map.h"
#include <cassert>
#include <utility>

Map::Map(int window_width, int window_height) {
  // todo (anyone)
  objects_.resize(columns_);
  for (auto &column : objects_) {
    column.resize(rows_);
  }
}

void Map::SetObject(std::unique_ptr<GameObject>&& object, int x, int y) {
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  objects_[x][y] = std::move(object);
}

const std::unique_ptr<GameObject>& Map::GetObject(int x, int y) const {
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  return objects_[x][y];
}

void Map::RemoveObject(int x, int y) {
  objects_[x][y] = nullptr;
}
