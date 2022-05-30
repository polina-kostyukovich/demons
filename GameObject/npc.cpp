#include "npc.h"

Npc::Npc(const Point& position, int boiler_height) :
    Creature(position), spawn_pos_(position), boiler_height_(boiler_height) {}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::Update(const Point& target_position) {
  if (is_born_) {
    UpdateFieldsIfBorn(target_position);
    return;
  }

  Vector2D direction;
  long double min_distance = constants::kMaxDistance;

  for (long double delta_x = -1;
       delta_x - 1. < constants::kEpsilon;
       delta_x += constants::kDirectionStep) {
    for (long double delta_y = -1;
         delta_y - 1. < constants::kEpsilon;
         delta_y += constants::kDirectionStep) {
      Vector2D new_direction(delta_x, delta_y);
      new_direction.Normalize();
      long double cur_distance =
          Point::Distance(position_ + new_direction * constants::kNpcStep,
                          target_position);
      if (cur_distance - min_distance < -constants::kEpsilon) {
        direction = new_direction;
        min_distance = cur_distance;
      }
    }
  }

  Move(direction);
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
    output.height = std::ceil(spawn_pos_.GetY() - position_.GetY());
    long double height_coef =
        (spawn_pos_.GetY() - position_.GetY()) / constants::kNpcSize;
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

void Npc::UpdateFieldsIfBorn(const Point& target_position) {
  position_ -= Point(0, constants::kNpcStep);
  is_moving_right_ =
      (position_.GetX() - target_position.GetX() < -constants::kEpsilon);
  if (spawn_pos_.GetY() - position_.GetY()
      > constants::kNpcSize + constants::kEpsilon) {
    is_born_ = false;
  }

  // todo hit_boxes
}
