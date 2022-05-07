#include "fireball.h"

#include <string>
#include <QPainter>

void Fireball::LoadPictures() {
  for (int i = 1; i < 5; i++) {
    std::string picture = ":Resources/Picture/Fireball/born_fireball";
    picture += std::to_string(i);
    picture += ".png";
    pictures_.emplace_back(picture.c_str());
  }
  for (int i = 1; i < 8; i++) {
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
    output.picture = pictures_[counter_ / constants::kSlowFireBall];
  } else {
    output.picture = pictures_[constants::kNumberBorn
        + counter_ / constants::kSlowFireBall];
  }
  return output;
}

void Fireball::Move() {
  if (!is_born_) {
    SetPosition(position_ + direction_ * constants::kFireballSpeed);
  }
}

bool Fireball::GetBool() {
  return is_born_;
}

void Fireball::SetBool(bool set) {
  is_born_ = set;
}

int Fireball::GetCounter() {
  return counter_;
}

void Fireball::SetCounter(int count) {
  counter_ = count;
}
