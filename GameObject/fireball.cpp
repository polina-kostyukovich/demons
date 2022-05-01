#include "fireball.h"

#include <QPainter>
#include <string>

void Fireball::LoadPictures() {
  std::string picture = ":Resources/Picture/Fireball/fireball1.png";
  pictures_.emplace_back(picture.c_str());
}

Picture Fireball::GetPicture() const {
  Picture output;
  Point pos = position_;

  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  pos.SetX(pos.GetX() - constants::kFireballSize / 1.5); // I don't know why (?)
  pos.SetY(pos.GetY() - constants::kFireballSize / 2);

  output.left_top = pos;
  output.picture = pictures_[0];
  return output;
}

void Fireball::Move() {
  SetPosition(position_ + direction_ * constants::kFireballSpeed);
}
