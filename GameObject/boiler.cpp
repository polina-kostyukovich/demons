#include "boiler.h"

void Boiler::LoadPictures() {
  picture_ = std::make_unique<QPixmap>(":Resources/Picture/StaticObject/boiler.png");
}

Picture Boiler::GetPicture() const {
  Picture result = {
      *picture_,
      position_,
      width_,
      height_
  };
  return result;
}
