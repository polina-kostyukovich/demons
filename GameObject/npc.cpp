#include <cmath>
#include <iostream>
#include <map>
#include <set>
#include <queue>

#include "npc.h"

Npc::Npc(const Point& position) : Creature(position) {}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::Update(const Point& target_position, const Map& map) {
  Vector2D row_direction(position_, target_position);
  row_direction.Normalize();
  if (CanMove(position_ + row_direction * constants::kNpcStep, map)) {
    Move(row_direction);
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
    std::pair<int, int> cur_cell = cells.front();
    cells.pop();

    for (auto& direction : directions) {
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
          CanMove(new_point, map)) {
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

bool Npc::CanMove(const Point& new_position, const Map& map) {
  int column = floor(new_position.GetX() / map.GetCellSize().first);
  int row = floor(new_position.GetY() / map.GetCellSize().second);

  if (column < 0 || row < 0) {
    return false;
  }

  if (map.GetObject(column, row).get() != nullptr) {
    return false;
  }
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
  output.width = output.height;
  output.left_top =
      position_ - Point(constants::kNpcSize / 2., constants::kNpcSize / 2.);
  if (is_moving_right_) {
    output.picture = pictures_[tick_counter_ / constants::kNpcSpeedCoefficient];
  } else {
    output.picture = pictures_[constants::kNumberOfEquallySidedNpc
        + tick_counter_ / constants::kNpcSpeedCoefficient];
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
