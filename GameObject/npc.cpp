#include "npc.h"

Npc::Npc(const Point& position) : Creature(position) {}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::Update(const Point& target_position) {
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
  if (direction.GetX() > 0) {
    is_move_right_ = true;
  } else {
    is_move_right_ = false;
  }
}

Picture Npc::GetPicture() const {
  Picture output;
  output.height = constants::kNpcSize;
  output.width = output.height;
  output.left_top = position_;
  if (is_move_right_) {
    output.picture = pictures_[tick_counter_ / constants::kNpcSpeedCoefficient];
  } else {
    output.picture = pictures_[constants::kNumberEquallySidedNpc
        + tick_counter_ / constants::kNpcSpeedCoefficient];
  }
  return output;
}

void Npc::InputPictures(std::string picture) {
  for (int i = 1; i <= constants::kNumberNpc; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
  picture += "_fight";
  for (int i = 1; i <= constants::kNumberFight; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
}

int Npc::GetCounter() {
  return tick_counter_;
}

void Npc::SetCounter(int counter) {
  tick_counter_ = counter;
}
