#include "fireball.h"

#include <QPainter>
#include <string>

void Fireball::LoadPicture() {
  std::string picture = ":Resources/Picture/Fireball/fireball1.png";
  pixmaps_.emplace_back(picture.c_str());
}

Picture Fireball::GetPicture() {
  Picture output;
  output.left_top = position_;
  output.width = constants::kFireballSize;
  output.height = constants::kFireballSize;

  QPixmap pixmap(pixmaps_[0]);
  QPainter painter(&pixmap);

  QPixmap image(pixmaps_[0].scaled(pixmap.width(), pixmap.height()));

  painter.drawPixmap(0, 0, image);
  output.picture = image;

  return output;
}
void Fireball::Move() {
  SetPosition(position_ + direction_ * constants::kFireballSpeed);
}
