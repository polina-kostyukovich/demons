#include "fireball.h"

#include <string>
#include <QPainter>

Fireball::Fireball(const Point &position, const Point &purpose) :
    DynamicObject(position), purpose_(purpose) {
  hit_box_.SetWidth(constants::kFireballSize
                    * constants::kFireballHitBoxWidthCoefficient);
  hit_box_.SetHeight(constants::kFireballSize
                     * constants::kFireballHitBoxHeightCoefficient);
  hit_box_.SetVerticalShift(
      (0.5 - constants::kFireballHitBoxHeightCoefficient / 2)
      * constants::kFireballSize);

  picture_above_hit_box_.SetWidth(
      constants::kFireballSize * constants::kFireballHitBoxWidthCoefficient);
  picture_above_hit_box_.SetHeight(
      constants::kFireballSize
      * (1.5 - constants::kFireballHitBoxHeightCoefficient));
  picture_above_hit_box_.SetVerticalShift(
      -(0.5 * hit_box_.GetHeight() - hit_box_.GetVerticalShift()));
}

void Fireball::LoadPictures() {
  for (int i = 1; i <= constants::kNumberOfBornFireballs; i++) {
    std::string picture = ":Resources/Picture/Fireball/born_fireball";
    picture += std::to_string(i);
    picture += ".png";
    pictures_.emplace_back(picture.c_str());
  }
  for (int i = 1; i <= constants::kNumberOfFireBall; i++) {
    std::string picture = ":Resources/Picture/Fireball/fireball";
    picture += std::to_string(i);
    picture += ".png";
    pictures_.emplace_back(picture.c_str());
  }
}

Picture Fireball::GetPicture() const {
  Picture output;

  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  output.left_top.SetX(position_.GetX() - constants::kFireballSize / 2);
  output.left_top.SetY(position_.GetY() - constants::kFireballSize / 2);

  if (is_born_) {
    output.picture =
        pictures_[tick_counter_ / constants::kFireballSpeedCoefficient];
  } else {
    output.picture = pictures_[constants::kNumberOfBornFireballs + tick_counter_
        / constants::kFireballSpeedCoefficient];
  }
  return output;
}

void Fireball::Move(const Point& spawn_pos) {
  if (!is_born_) {
    SetPosition(position_ + direction_ * constants::kFireballSpeed);
  } else {
    SetPosition(spawn_pos);
  }
}

bool Fireball::IsBorn() {
  return is_born_;
}

void Fireball::SetBorn(bool is_born) {
  is_born_ = is_born;
}

int Fireball::GetCounter() {
  return tick_counter_;
}

void Fireball::SetCounter(int count) {
  tick_counter_ = count;
}

void Fireball::CreateDirection() {
  direction_ = Vector2D(position_, purpose_);
  direction_.Normalize();
}
Point Fireball::GetPurpose() const {
  return purpose_;
}
