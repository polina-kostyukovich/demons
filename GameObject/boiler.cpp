#include "boiler.h"

void Boiler::LoadPictures() {
  picture_ =
      std::make_unique<QPixmap>(":Resources/Picture/StaticObject/boiler.png");
}

Picture Boiler::GetPicture() const {
  Picture result = {
      *picture_,
      position_ - Point(width_ / 2., height_ / 2.),
      width_,
      height_
  };
  return result;
}
