#include "model.h"

Model::Model(std::unique_ptr<View>&& view) :
    view_(std::move(view)),
    map_(0, 0),
    hero_({0, 0}) {
  // todo
}

void Model::SetPressedKey(int key) {
  keys_[key] = true;
}

void Model::UnsetPressedKey(int key) {
  keys_[key] = false;
}

void Model::ProcessPressedKeys() {
  MoveHero();
}

Vector2D Model::GetDirection() const {
  Vector2D direction;
  if (keys_.contains(Qt::Key_Left) && keys_.at(Qt::Key_Left)
      || keys_.contains(Qt::Key_A) && keys_.at(Qt::Key_A)) {
    direction += {-1, 0};
  }
  if (keys_.contains(Qt::Key_Up) && keys_.at(Qt::Key_Up)
      || keys_.contains(Qt::Key_W) && keys_.at(Qt::Key_W)) {
    direction += {0, -1};
  }
  if (keys_.contains(Qt::Key_Right) && keys_.at(Qt::Key_Right)
      || keys_.contains(Qt::Key_D) && keys_.at(Qt::Key_D)) {
    direction += {1, 0};
  }
  if (keys_.contains(Qt::Key_Down) && keys_.at(Qt::Key_Down)
      || keys_.contains(Qt::Key_S) && keys_.at(Qt::Key_S)) {
    direction += {0, 1};
  }
  direction.Normalize();
  return direction;
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
}

void Model::MoveHero() {
  Vector2D direction = GetDirection();
  auto cell = GetCellCoordinatesOnMap(hero_.GetPoint());

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

  hero_.SetPoint(hero_.GetPoint() + constants::kHeroStep * direction);
}
