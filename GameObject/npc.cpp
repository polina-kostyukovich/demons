#include <cmath>
#include <iostream>
#include <map>
#include <set>

#include "npc.h"

Npc::Npc(const Point& position) : Creature(position) {}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::Update(const Point& target_position, const Map& map) {
  std::set<ProcessingPoint> points_order;
  std::map<ProcessingPoint, bool> point_is_used;
  std::map<ProcessingPoint, ProcessingPoint> previous_point;

  ProcessingPoint start_point({position_,
                               Point::Distance(position_, target_position)});
  points_order.insert(start_point);
  point_is_used[start_point] = true;
  previous_point[start_point] = start_point;

  ProcessingPoint end_point;

  bool hero_was_riched = false;

  std::vector<Vector2D> directions;
  for (int delta_x = -1; delta_x <= 1; delta_x++) {
    for (int delta_y = -1; delta_y <= 1; delta_y++) {
      directions.emplace_back(delta_x, delta_y);
    }
  }
  directions.emplace_back(position_, target_position);

  while (!hero_was_riched) {
    ProcessingPoint cur_point = *points_order.begin();
    points_order.erase(points_order.begin());

    if (Point::Distance(cur_point.position_, target_position) <=
        constants::kClose) {
      hero_was_riched = true;
      end_point = cur_point;
      break;
    }

    directions.pop_back();
    directions.emplace_back(cur_point.position_, target_position);

    for (auto& new_direction : directions) {
      new_direction.Normalize();

      ProcessingPoint new_point;
      new_point.position_ = cur_point.position_ +
                            new_direction * constants::kNpcStep;
      new_point.weight_ = Point::Distance(new_point.position_,
                                          target_position);
      if (CanMove(new_point.position_, map) &&
          !point_is_used[new_point]) {
        previous_point[new_point] = cur_point;
        point_is_used[new_point] = true;
        points_order.insert(new_point);
      }
    }
  }

  bool next_point_found = false;
  while (!next_point_found) {
    if (previous_point[end_point] == start_point) {
      next_point_found = true;
    } else {
      end_point = previous_point[end_point];
    }
  }
  Vector2D direction(position_, end_point.position_);
  direction.Normalize();
  Move(direction);
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

Npc::ProcessingPoint::ProcessingPoint(const Point &position,
                                      long double weight) :
    position_(position),
    weight_(weight) {}

bool Npc::ProcessingPoint::operator<(
    const Npc::ProcessingPoint &second) const {
  if (abs(weight_ - second.weight_) > constants::kEpsilon) {
    return weight_ - second.weight_ < -constants::kEpsilon;
  }
  if (abs(position_.GetX() - second.position_.GetX()) < constants::kEpsilon) {
    return position_.GetY() - second.position_.GetY() < -constants::kEpsilon;
  } else {
    return position_.GetX() - second.position_.GetX() < -constants::kEpsilon;
  }
}

bool Npc::ProcessingPoint::operator==(
    const Npc::ProcessingPoint &second) const {
  return (abs(position_.GetX() - second.position_.GetX()) <
          constants::kEpsilon) &&
         (abs(position_.GetY() - second.position_.GetY()) <
          constants::kEpsilon) &&
         (abs(weight_ - second.weight_) < constants::kEpsilon);
}
