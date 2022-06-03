#include "npc.h"

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
                 const std::vector<Npc>& npc_list) {
  if (is_born_) {
    UpdateFieldsIfBorn(target_position, map, npc_list);
    return;
  }

  if (position_.GetX() - target_position.GetX() < -constants::kEpsilon) {
    is_moving_right_ = true;
  } else {
    is_moving_right_ = false;
  }

  Vector2D raw_direction(position_, target_position);
  raw_direction.Normalize();
  long double length = Point::Distance(position_, target_position) -
      constants::kEpsilon;
  if (!(length - constants::kNpcStep < -constants::kEpsilon)) {
    length = constants::kNpcStep;
  }
  length -= constants::kEpsilon;

  if (CanMove(position_ + raw_direction * length, map, npc_list)) {
    Move(raw_direction * (length / constants::kNpcStep));
    return;
  }

  int grid_columns = map.GetColumnsNumber() * map.GetCellSize().first /
      constants::kNpcStep;
  int grid_rows = map.GetRowsNumber() * map.GetCellSize().second /
      constants::kNpcStep;

  std::vector<std::vector<Cell>> previous_cell(
      grid_columns, std::vector<Cell>(grid_rows, Cell()));
  std::vector<std::vector<bool>> cell_is_used(
      grid_columns, std::vector<bool>(grid_rows, false));

  std::set<Cell> cells;

  Cell start_cell(
      floor(position_.GetX() / constants::kNpcStep),
      floor(position_.GetY() / constants::kNpcStep),
      Point::Distance(position_, target_position));

  long double addition_x = position_.GetX() - (start_cell.x *
      constants::kNpcStep);
  long double addition_y = position_.GetY() - (start_cell.y *
      constants::kNpcStep);

  cells.insert(start_cell);
  cell_is_used[start_cell.x][start_cell.y] = true;
  previous_cell[start_cell.x][start_cell.y] = start_cell;

  Cell end_cell(
      floor(target_position.GetX() / constants::kNpcStep),
      floor(target_position.GetY() / constants::kNpcStep),
      0.);
  Point end_point(end_cell.x * constants::kNpcStep + addition_x,
                  end_cell.y * constants::kNpcStep + addition_y);
  end_cell.weight = Point::Distance(end_point, target_position);

  Cell extra_cell;
  extra_cell.weight = 2. * Point::Distance(position_, target_position);

  std::vector<std::pair<int, int>> directions = {
      {1, 0}, {-1, 0}, {0, 1}, {0, -1},
      {1, 1}, {-1, -1}, {-1, 1}, {1, -1}
  };
  int operations = 0;
  while (!cell_is_used[end_cell.x][end_cell.y]) {
    if (cells.empty()) {
      break;
    }
    operations++;
    if (operations > constants::kNumberOfOperations) {
      break;
    }
    Cell cur_cell = *cells.begin();
    cells.erase(cells.begin());

    if (cur_cell.weight - extra_cell.weight < -constants::kEpsilon) {
      extra_cell = cur_cell;
    }

    for (const auto& direction : directions) {
      Cell new_cell = cur_cell;
      new_cell.x += direction.first;
      new_cell.y += direction.second;

      if (new_cell.x < 0 || new_cell.y < 0 ||
          new_cell.x >= grid_columns || new_cell.y >= grid_rows ||
          cell_is_used[new_cell.x][new_cell.y]) {
        continue;
      }

      Point new_point(new_cell.x * constants::kNpcStep + addition_x,
                      new_cell.y * constants::kNpcStep + addition_y);
      new_cell.weight = Point::Distance(new_point, target_position);
      cell_is_used[new_cell.x][new_cell.y] = true;
      if (CanMove(new_point, map, npc_list)) {
        cells.insert(new_cell);
        previous_cell[new_cell.x][new_cell.y] = cur_cell;
      }
    }
  }

  Cell previous_end_cell = previous_cell[end_cell.x][end_cell.y];
  if (previous_end_cell ==
      previous_cell[previous_end_cell.x][previous_end_cell.y]) {
    end_cell = extra_cell;
  }

  while (!(previous_cell[end_cell.x][end_cell.y] == start_cell)) {
    end_cell = previous_cell[end_cell.x][end_cell.y];
    operations++;
  }
  end_point = Point(end_cell.x * constants::kNpcStep + addition_x,
                    end_cell.y * constants::kNpcStep + addition_y);
  Vector2D cur_direction(position_, end_point);
  cur_direction.Normalize();
  Move(cur_direction);
}

bool Npc::CanMove(const Point& new_position, const Map& map,
                  const std::vector<Npc>& npc_list) {
  int left_column = floor((new_position.GetX() - GetHitBox().GetWidth() / 2.)
      / map.GetCellSize().first);
  int top_row = floor((new_position.GetY() - GetHitBox().GetHeight() / 2.)
      / map.GetCellSize().second);

  int right_column = floor((new_position.GetX() + GetHitBox().GetWidth() / 2.)
      / map.GetCellSize().first);
  int bottom_row = floor((new_position.GetY() + GetHitBox().GetHeight() / 2.)
      / map.GetCellSize().second);


  if (top_row < 0 || left_column < 0 ||
      bottom_row >= map.GetRowsNumber() ||
      right_column >= map.GetColumnsNumber()) {
    return false;
  }

  if (map.GetObject(floor(new_position.GetX() / map.GetCellSize().first),
                    floor(new_position.GetY() / map.GetCellSize().second))
                    != nullptr) {
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
                             const std::vector<Npc>& npc_list) {
  position_ -= Point(0, constants::kNpcStep);
  if (IsCollidedWithNpc(npc_list)) {
    position_ += Point(0, constants::kNpcStep);
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

bool Npc::IsCollidedWithNpc(const std::vector<Npc>& npc_list) const {
  for (const auto& npc : npc_list) {
    if (position_ == npc.position_) {
      continue;
    }
    if (GetHitBox().IsCollided(npc.GetHitBox())) {
      return true;
    }
  }
  return false;
}

bool Npc::Cell::operator==(const Cell& another_cell) const {
  return (abs(weight - another_cell.weight) < constants::kEpsilon) &&
          x == another_cell.x &&
          y == another_cell.y;
}

bool Npc::Cell::operator<(const Cell& another_cell) const {
  if (abs(weight - another_cell.weight) < constants::kEpsilon) {
    if (x == another_cell.x) {
      return y < another_cell.y;
    }
    return x < another_cell.x;
  } else {
    return (weight - another_cell.weight < -constants::kEpsilon);
  }
}
