#include "map.h"

#include <cassert>
#include <utility>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

int Map::GetColumnsNumber() const {
  return columns_;
}

int Map::GetRowsNumber() const {
  return rows_;
}

void Map::SetObject(const std::shared_ptr<StaticObject>& object, int x, int y) {
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  objects_[x][y] = object;
  RemakeVectorOfObjects();
}

const std::shared_ptr<StaticObject>& Map::GetObject(int x, int y) const {
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  return objects_[x][y];
}

void Map::RemoveObject(int x, int y) {
  assert(x >= 0 && x < columns_ && y >= 0 && y < rows_);
  objects_[x][y] = nullptr;
  RemakeVectorOfObjects();
}

void Map::LoadPictures() {
  QPixmap pixmap(width_, height_);
  QPainter painter_pixmap(&pixmap);

  QPixmap lava = QPixmap(":Resources/Picture/StaticObject/lava.png");
  QPixmap horizontal_wall =
      QPixmap(":Resources/Picture/StaticObject/horizontal_wall.png");
  QPixmap vertical_wall =
      QPixmap(":Resources/Picture/StaticObject/vertical_wall.png");
  for (int x = 0; x < width_; x += constants::kLavaSize) {
    for (int y = 0; y < height_; y += constants::kLavaSize) {
      painter_pixmap.drawPixmap(x, y, constants::kLavaSize,
                                constants::kLavaSize, lava);
    }
  }
  for (int x = 0; x < width_; x += constants::kWallSize) {
    painter_pixmap.drawPixmap(x, 0, constants::kWallSize,
                              constants::kWallSize, horizontal_wall);
    painter_pixmap.drawPixmap(x,
                              height_ - constants::kWallSize,
                              constants::kWallSize,
                              constants::kWallSize,
                              horizontal_wall);
  }
  for (int y = 0; y < height_; y += constants::kWallSize) {
    painter_pixmap.drawPixmap(0, y, constants::kWallSize,
                              constants::kWallSize, vertical_wall);
    painter_pixmap.drawPixmap(width_ - constants::kWallSize, y,
                              constants::kWallSize,
                              constants::kWallSize,
                              vertical_wall);
  }
  picture_ = pixmap;

  Boiler::LoadPictures();
}

Picture Map::GetPicture() const {
  Picture output;
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

void Map::LoadBoilers() {
  QFile file(":Resources/Jsons/boilers_data.json");
  file.open(QIODevice::ReadOnly | QIODevice::Text);

  QJsonDocument document =
      QJsonDocument::fromJson(file.readAll());
  QJsonObject object = document.object();
  columns_ = object["NumberOfColumns"].toInt();
  rows_ = object["NumberOfRows"].toInt();

  QJsonArray boilers_coords =
      object["BoilersCoordinates"].toArray();
  objects_ = std::vector<std::vector<std::shared_ptr<StaticObject>>>(
      columns_, std::vector<std::shared_ptr<StaticObject>>(rows_));

  int boiler_width = width_ / columns_;
  int boiler_height = height_ / rows_;

  for (const auto& boiler_coords: boilers_coords) {
    int column = boiler_coords.toObject().value("x").toInt();
    int row = boiler_coords.toObject().value("y").toInt();
    Point position(column * boiler_width + boiler_width / 2.,
                   row * boiler_height + boiler_height / 2.);
    objects_[column][row] =
        std::make_shared<Boiler>(position, boiler_width, boiler_height);
  }

  RemakeVectorOfObjects();
}

const std::vector<std::shared_ptr<StaticObject>>& Map::GetObjects() const {
  return objects_vector_;
}

std::pair<int, int> Map::GetCellSize() const {
  int cell_width = width_ / columns_;
  int cell_height = height_ / rows_;
  return {cell_width, cell_height};
}

std::pair<int, int> Map::GetCellCoordinatesOnMap(const Point& point) const {
  auto cell = GetCellSize();
  int x = static_cast<int>(point.GetX() / cell.first);
  if (x == columns_) {
    x = columns_ - 1;
  }
  int y = static_cast<int>(point.GetY() / cell.second);
  if (y == rows_) {
    y = rows_ - 1;
  }
  return {x, y};
}

void Map::RemakeVectorOfObjects() {
  objects_vector_.clear();
  for (int i = 0; i < columns_; ++i) {
    for (int j = 0; j < rows_; ++j) {
      if (objects_[i][j] != nullptr) {
        objects_vector_.emplace_back(objects_[i][j]);
      }
    }
  }
}
