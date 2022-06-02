#include "npc.h"

#include <iostream>

#include <algorithm>
#include <cmath>
#include <queue>
#include <set>
#include <utility>

Npc::Npc(const Point& position,
         const std::weak_ptr<StaticObject>& native_boiler) :
    Creature(position), native_boiler_(native_boiler) {
  hit_box_.SetWidth(constants::kNpcSize
                        * constants::kNpcHitBoxWidthCoefficient);
  hit_box_.SetHeight(0);
  hit_box_.SetVerticalShift(0);

  picture_above_hit_box_.SetWidth(hit_box_.GetWidth());
  picture_above_hit_box_.SetHeight(
      constants::kNpcSize * (1 - constants::kNpcHitBoxHeightCoefficient));
  picture_above_hit_box_.SetVerticalShift(
      -(0.5 - (1 - constants::kNpcHitBoxHeightCoefficient) / 2)
          * constants::kNpcSize);
}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::Update(const Point& target_position, const Map& map,
                 std::vector<Npc>& npc_list) {
  if (is_born_) {
    UpdateFieldsIfBorn(target_position, map, npc_list);
    return;
  }

  Vector2D raw_direction(position_, target_position);
  raw_direction.Normalize();
  if (CanMove(position_ + raw_direction * constants::kNpcStep, map, npc_list)) {
    Move(raw_direction);
    return;
  }

  int grid_columns = map.GetColumnsNumber() * map.GetCellSize().first /
      constants::kNpcStep;
  int grid_rows = map.GetRowsNumber() * map.GetCellSize().second /
      constants::kNpcStep;

  std::vector<std::vector<std::pair<int, int>>> previous_cell(
      grid_columns, std::vector<std::pair<int, int>>(grid_rows, {0, 0}));
  std::vector<std::vector<bool>> cell_is_used(
      grid_columns, std::vector<bool>(grid_rows, false));

  std::queue<std::pair<int, int>> cells;

  std::pair<int, int> start_cell(
      floor(position_.GetX() / constants::kNpcStep),
      floor(position_.GetY() / constants::kNpcStep));

  long double addition_x = position_.GetX() - start_cell.first *
      constants::kNpcStep;
  long double addition_y = position_.GetY() - start_cell.second *
      constants::kNpcStep;

  cells.push(start_cell);
  cell_is_used[start_cell.first][start_cell.second] = true;
  previous_cell[start_cell.first][start_cell.second] = start_cell;

  std::pair<int, int> end_cell(
      floor(target_position.GetX() / constants::kNpcStep),
      floor(target_position.GetY() / constants::kNpcStep));

  std::vector<Vector2D> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1}
  };

  while (!cell_is_used[end_cell.first][end_cell.second]) {
    if (cells.empty()) {
      break;
    }
    std::pair<int, int> cur_cell = cells.front();
    cells.pop();

    for (const auto& direction : directions) {
      std::pair<int, int> new_cell = cur_cell;
      new_cell.first += direction.GetX();
      new_cell.second += direction.GetY();

      if (new_cell.first < 0 || new_cell.second < 0 ||
          new_cell.first >= grid_columns || new_cell.second >= grid_rows) {
        continue;
      }

      Point new_point(new_cell.first * constants::kNpcStep + addition_x,
                      new_cell.second * constants::kNpcStep + addition_y);

      if (!cell_is_used[new_cell.first][new_cell.second] &&
          CanMove(new_point, map, npc_list)) {
        cells.push(new_cell);
        cell_is_used[new_cell.first][new_cell.second] = true;
        previous_cell[new_cell.first][new_cell.second] = cur_cell;
      }
    }
  }

  while (previous_cell[end_cell.first][end_cell.second] != start_cell) {
    end_cell = previous_cell[end_cell.first][end_cell.second];
  }

  Point end_point(end_cell.first * constants::kNpcStep + addition_x,
                  end_cell.second * constants::kNpcStep + addition_y);
  Vector2D cur_direction(position_, end_point);
  cur_direction.Normalize();
  Move(cur_direction);
}

bool Npc::CanMove(const Point& new_position, const Map& map,
                  std::vector<Npc>& npc_list) {
  int row = floor(new_position.GetY() / map.GetCellSize().second);
  int column = floor(new_position.GetX() / map.GetCellSize().first);

  if (row < 0 || column < 0 ||
      row >= map.GetRowsNumber() ||
      column >= map.GetColumnsNumber()) {
    return false;
  }

  if (map.GetObject(column, row) != nullptr) {
    return false;
  }

  Point old_position = position_;
  position_ = new_position;
  if (IsCollidedWithNpc(npc_list)) {
    position_ = old_position;
    return false;
  }
  position_ = old_position;

  return true;
}

void Npc::Move(const Vector2D& direction) {
  SetPosition(position_ + direction * constants::kNpcStep);
  if (direction.GetX() > constants::kEpsilon) {
    is_moving_right_ = true;
  } else {
    is_moving_right_ = false;
  }
}

Picture Npc::GetPicture() const {
  Picture output;
  output.height = constants::kNpcSize;
  output.width = constants::kNpcSize;
  output.left_top =
      position_ - Point(constants::kNpcSize / 2., constants::kNpcSize / 2.);
  if (is_moving_right_) {
    output.picture = pictures_[tick_counter_ / constants::kNpcSpeedCoefficient];
  } else {
    output.picture = pictures_[constants::kNumberOfEquallySidedNpc
        + tick_counter_ / constants::kNpcSpeedCoefficient];
  }

  if (is_born_) {
    output.height = std::max(0, static_cast<int>(std::ceil(
        native_boiler_.lock()->GetPosition().GetY() - position_.GetY()
        - native_boiler_.lock()->GetHeight() / 2 + constants::kNpcSize / 2)));

    long double height_coef =
        static_cast<long double>(output.height) / constants::kNpcSize;

    output.picture = output.picture.copy(
        0, 0, output.picture.width(),
        std::ceil(height_coef * output.picture.height()));
  }
  return output;
}

void Npc::InputPictures(std::string picture) {
  for (int i = 1; i <= constants::kNumberOfNpc; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
  picture += "_fight";
  for (int i = 1; i <= constants::kNumberOfFightingNpc; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
}

int Npc::GetCounter() const {
  return tick_counter_;
}

void Npc::SetCounter(int counter) {
  tick_counter_ = counter;
}

void Npc::UpdateFieldsIfBorn(const Point& target_position, const Map& map,
                             std::vector<Npc>& npc_list) {
  position_ -= Point(0, constants::kNpcStep);
  if (IsCollidedWithNpc(npc_list)) {
    position_ += Point(0, constants::kNpcStep);
  } else {
    std::cerr << "Est shag\n";
  }

  is_moving_right_ =
      (position_.GetX() - target_position.GetX() < -constants::kEpsilon);

  if (native_boiler_.lock()->GetPosition().GetY() - position_.GetY()
      > constants::kNpcSize / 2 + native_boiler_.lock()->GetHeight() / 2
          + constants::kEpsilon) {
    is_born_ = false;
  }

  long double boiler_hit_box_top =
      native_boiler_.lock()->GetPosition().GetY()
          + native_boiler_.lock()->GetHitBox().GetVerticalShift()
          - native_boiler_.lock()->GetHitBox().GetHeight() / 2;

  long double visible_height =
      boiler_hit_box_top - position_.GetY() + constants::kNpcSize / 2;

  hit_box_.SetHeight(std::min(
      visible_height - picture_above_hit_box_.GetHeight(),
      constants::kNpcHitBoxHeightCoefficient * constants::kNpcSize));

  hit_box_.SetVerticalShift(
      picture_above_hit_box_.GetHeight() + hit_box_.GetHeight() / 2
          - constants::kNpcSize / 2);
}

Point Npc::GetSpawnPos() const {
  return native_boiler_.lock()->GetPosition();
}

bool Npc::IsCollidedWithNpc(std::vector<Npc>& npc_list) const {
  for (const auto& npc : npc_list) {
    if (position_ == npc.position_) {
      continue;
    }
    if (GetHitBox().IsCollided(npc.GetHitBox())) {
      return false;
    }
  }
  return true;
}
