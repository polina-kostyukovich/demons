#include "model.h"

Model::Model(std::unique_ptr<View>&& view) :
    view_(std::move(view)),
    map_(0, 0),
    hero_({0, 0}) {
  // todo
}

const Hero& Model::GetHero() {
  return hero_;
}

void Model::MoveHero(Vector2D direction) {
  auto cell = GetCellCoordinatesOnMap(hero_.GetPosition());

  if (direction.GetX() < -constants::kEpsilon && (cell.first == 0
      || map_.GetObject(cell.first - 1, cell.second) != nullptr)) {
    direction.SetX(0);
  }
  if (direction.GetX() > constants::kEpsilon
      && (cell.first == map_.GetColumnsNumber() - 1
          || map_.GetObject(cell.first + 1, cell.second) != nullptr)) {
    direction.SetX(0);
  }
  if (direction.GetY() < -constants::kEpsilon && (cell.second == 0
      || map_.GetObject(cell.first, cell.second - 1) != nullptr)) {
    direction.SetY(0);
  }
  if (direction.GetY() > constants::kEpsilon
      && (cell.second == map_.GetRowsNumber() - 1
          || map_.GetObject(cell.first, cell.second + 1) != nullptr)) {
    direction.SetY(0);
  }

  hero_.SetPosition(hero_.GetPosition() + constants::kHeroStep * direction);
}

std::pair<int, int> Model::GetCellSize() const {
  int width = view_->GetWindowWidth() / map_.GetColumnsNumber();
  int height = view_->GetWindowHeight() / map_.GetRowsNumber();
  return {width, height};
}

std::pair<int, int> Model::GetCellCoordinatesOnMap(const Point& point) const {
  auto cell = GetCellSize();
  int x = static_cast<int>(point.GetX() / cell.first);
  int y = static_cast<int>(point.GetY() / cell.second);
  return {x, y};
