#include "map.h"

#include <cassert>
#include <utility>

Map::Map() {
  // todo write json
  objects_.resize(columns_);
  for (auto& column : objects_) {
    column.resize(rows_);
  }
}

int Map::GetColumnsNumber() const {
  return columns_;
}

int Map::GetRowsNumber() const {
  return rows_;
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
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  objects_[x][y] = nullptr;
}

void Map::LoadPictures() {
  QPixmap pixmap(width_, height_);
  QPainter painter_pixmap(&pixmap);

  QPixmap lava = QPixmap(":Resources/Picture/StaticObject/lava.png");
  QPixmap horizontal_wall =
      QPixmap(":Resources/Picture/StaticObject/horizontal_wall.png");
  QPixmap vertical_wall =
      QPixmap(":Resources/Picture/StaticObject/vertical_wall.png");
  for (int i = 0; i <= width_ / constants::kLavaSize; i++) {
    for (int j = 0; j <= height_ / constants::kLavaSize; j++) {
      painter_pixmap.drawPixmap(i * constants::kLavaSize,
                                j * constants::kLavaSize,
                                constants::kLavaSize,
                                constants::kLavaSize,
                                lava);
    }
  }
  for (int i = 0; i <= width_ / constants::kWallSize; i++) {
    painter_pixmap.drawPixmap(i * constants::kWallSize, 0, constants::kWallSize,
                              constants::kWallSize, horizontal_wall);
    painter_pixmap.drawPixmap(i * constants::kWallSize,
                              height_ - constants::kWallSize,
                              constants::kWallSize,
                              constants::kWallSize,
                              horizontal_wall);
  }
  for (int j = 0; j <= height_ / constants::kWallSize; j++) {
    painter_pixmap.drawPixmap(0, j * constants::kWallSize, constants::kWallSize,
                              constants::kWallSize, vertical_wall);
    painter_pixmap.drawPixmap(width_ - constants::kWallSize,
                              j * constants::kWallSize,
                              constants::kWallSize,
                              constants::kWallSize,
                              vertical_wall);
  }
  picture_ = pixmap;
}

Animation Map::GetAnimation(int counter) const {
  Animation output;
  output.left_top = Point(0., 0.);
  output.picture = picture_;
  output.width = width_;
  output.height = height_;
  return output;
}

void Map::SetSize(int width, int height) {
  width_ = width;
  height_ = height;
}
