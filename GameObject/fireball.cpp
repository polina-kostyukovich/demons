#include "fireball.h"

#include <string>
#include <QPainter>

void Fireball::LoadPictures() {
  for (int i = 1; i <= constants::kNumberBorn; i++) {
    std::string picture = ":Resources/Picture/Fireball/born_fireball";
    picture += std::to_string(i);
    picture += ".png";
    pictures_.emplace_back(picture.c_str());
  }
  for (int i = 1; i <= constants::kNumberFireBall; i++) {
    std::string picture = ":Resources/Picture/Fireball/fireball";
    picture += std::to_string(i);
    picture += ".png";
    pictures_.emplace_back(picture.c_str());
  }
}

Picture Fireball::GetPicture() const {
  Picture output;
  output.left_top = position_;

  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  output.left_top.SetX(position_.GetX() - constants::kFireballSize / 2);
  output.left_top.SetY(position_.GetY() - constants::kFireballSize / 2);

  if (is_born_) {
    output.picture =
        pictures_[tick_counter_ / constants::kFireballSpeedCoefficient];
  } else {
    output.picture = pictures_[constants::kNumberBorn + tick_counter_ /
        constants::kFireballSpeedCoefficient];
  }
  return output;
}

void Fireball::Move() {
  if (!is_born_) {
    SetPosition(position_ + direction_ * constants::kFireballSpeed);
  } else {
    SetPosition(spawn_pos_);
  }
}

bool Fireball::IsBorn() {
  return is_born_;
}

void Fireball::SetBorn(bool set) {
  is_born_ = set;
}

int Fireball::GetCounter() {
  return tick_counter_;
}

void Fireball::SetCounter(int count) {
  tick_counter_ = count;
}

void Fireball::SetSpawnPos(const Point& pos) {
  spawn_pos_ = pos;
}
