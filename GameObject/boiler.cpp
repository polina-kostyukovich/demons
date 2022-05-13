#include "boiler.h"

Boiler::Boiler(const Point& position, int width, int height) :
    StaticObject(position),
    width_(width),
    height_(height) {
  hit_box_.SetWidth(width_);
  hit_box_.SetHeight(height_ * constants::kBoilerHitBoxHeightCoefficient);
  hit_box_.SetVerticalShift(
      (0.5 - constants::kBoilerHitBoxHeightCoefficient / 2) * height_);

  picture_above_hit_box_.SetWidth(width_);
  picture_above_hit_box_.SetHeight(height_ - hit_box_.GetHeight());
  picture_above_hit_box_.SetVerticalShift(
      -(0.5 * height_ - hit_box_.GetVerticalShift()));
}

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
