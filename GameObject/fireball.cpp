#include "fireball.h"

#include <QPainter>
#include <string>

void Fireball::LoadPicture() {
  std::string picture = ":Resources/Picture/Fireball/fireball1.png";
  pixmaps_.emplace_back(picture.c_str());
}

Picture Fireball::GetPicture() const {
  Picture output;
  Point pos = position_;

  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  pos.SetX(pos.GetX() - output.width / 2);
  pos.SetY(pos.GetY() - output.height / 2);

  output.left_top = pos;
  output.picture = pixmaps_[0];
  return output;
}

void Fireball::Move() {
  SetPosition(position_ + direction_ * constants::kFireballSpeed);
}
