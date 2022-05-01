#include "fireball.h"

#include <QPainter>
#include <string>

void Fireball::LoadPictures() {
  std::string picture = ":Resources/Picture/Fireball/fireball1.png";
  pictures_.emplace_back(picture.c_str());
}

Picture Fireball::GetPicture() const {
  Picture output;
  output.left_top = position_;

  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  output.left_top.SetX(position_.GetX() -
                       constants::kFireballSize / 1.5); // I don't know why (?)
  output.left_top.SetY(position_.GetY() - constants::kFireballSize / 2);

  output.picture = pictures_[0];
  return output;
}

void Fireball::Move() {
  SetPosition(position_ + direction_ * constants::kFireballSpeed);
}
