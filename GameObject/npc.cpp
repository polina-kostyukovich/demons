#include "npc.h"

#include <algorithm>
#include <cmath>

Npc::Npc(const Point& position,
         const std::weak_ptr<StaticObject>& native_boiler) :
    Creature(position), native_boiler_(native_boiler) {
  hit_box_.SetWidth(constants::kNpcSize
                        * constants::kNpcHitBoxWidthCoefficient);
  hit_box_.SetHeight(0);
  hit_box_.SetVerticalShift(0);

  picture_above_hit_box_.SetWidth(hit_box_.GetWidth());
  picture_above_hit_box_.SetHeight(
      constants::kNpcSize * (1 - constants::kNpcHitBoxHeightCoefficient));
  picture_above_hit_box_.SetVerticalShift(
      -(0.5 - (1 - constants::kNpcHitBoxHeightCoefficient) / 2)
          * constants::kNpcSize);
}

void Npc::LoadPictures() {
  std::string picture = ":Resources/Picture/Npc/npc";
  InputPictures(picture);
  picture += "_left";
  InputPictures(picture);
}

void Npc::InputPictures(std::string picture) {
  for (int i = 1; i <= constants::kNumberOfNpc; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
  picture += "_fight";
  for (int i = 1; i <= constants::kNumberOfRaisingHandNpc; i++) {
    pictures_.emplace_back((picture + std::to_string(i) + ".png").c_str());
  }
  pictures_.emplace_back(((picture
      + std::to_string(constants::kNumberOfRaisingHandNpc)) + ".png").c_str());
  for (int i = 0; i < (constants::kNumberOfRaisingHandNpc - 1); i++) {
    pictures_.emplace_back((picture
        + std::to_string(constants::kNumberOfRaisingHandNpc - i)
        + ".png").c_str());
  }
}

void Npc::Update(const Point& target_position) {
  if (is_born_) {
    UpdateFieldsIfBorn(target_position);
    return;
  }

  Vector2D direction;
  long double min_distance = constants::kMaxDistance;

  for (long double delta_x = -1;
       delta_x - 1. < constants::kEpsilon;
       delta_x += constants::kDirectionStep) {
    for (long double delta_y = -1;
         delta_y - 1. < constants::kEpsilon;
         delta_y += constants::kDirectionStep) {
      Vector2D new_direction(delta_x, delta_y);
      new_direction.Normalize();
      long double cur_distance =
          Point::Distance(position_ + new_direction * constants::kNpcStep,
                          target_position);
      if (cur_distance - min_distance < -constants::kEpsilon) {
        direction = new_direction;
        min_distance = cur_distance;
      }
    }
  }

  if (!is_fighting_) {
    Move(direction);
  }
}

void Npc::Move(const Vector2D& direction) {
  SetPosition(position_ + direction * constants::kNpcStep);
  if (direction.GetX() > constants::kEpsilon) {
    is_moving_right_ = true;
  } else {
    is_moving_right_ = false;
  }
}

Picture Npc::GetPicture() const {
  Picture output;
  output.height = constants::kNpcSize;
  output.width = constants::kNpcSize;
  output.left_top =
      position_ - Point(constants::kNpcSize / 2., constants::kNpcSize / 2.);

  if (!is_fighting_) {
    if (is_moving_right_) {
      output.picture =
          pictures_[tick_counter_ / constants::kNpcSpeedCoefficient];
    } else {
      output.picture = pictures_[constants::kNumberOfEquallySidedNpc
          + tick_counter_ / constants::kNpcSpeedCoefficient];
    }
  } else {
    if (is_moving_right_) {
      output.picture = pictures_[constants::kNumberOfNpc
          + tick_counter_ / constants::kNpcSpeedCoefficient];
    } else {
      output.picture = pictures_[constants::kNumberOfEquallySidedNpc
          + constants::kNumberOfNpc
          + tick_counter_ / constants::kNpcSpeedCoefficient];
    }
  }

  if (is_born_) {
    output.height = std::max(0, static_cast<int>(std::ceil(
        native_boiler_.lock()->GetPosition().GetY() - position_.GetY()
            - native_boiler_.lock()->GetHeight() / 2
            + constants::kNpcSize / 2)));

    long double height_coef =
        static_cast<long double>(output.height) / constants::kNpcSize;

    output.picture = output.picture.copy(
        0, 0, output.picture.width(),
        std::ceil(height_coef * output.picture.height()));
  }
  return output;
}

int Npc::GetCounter() const {
  return tick_counter_;
}

void Npc::SetCounter(int counter) {
  tick_counter_ = counter;
}

void Npc::UpdateFieldsIfBorn(const Point& target_position) {
  position_ -= Point(0, constants::kNpcStep);
  is_moving_right_ =
      (position_.GetX() - target_position.GetX() < -constants::kEpsilon);

  if (native_boiler_.lock()->GetPosition().GetY() - position_.GetY()
      > constants::kNpcSize / 2 + native_boiler_.lock()->GetHeight() / 2
          + constants::kEpsilon) {
    is_born_ = false;
  }

  long double boiler_hit_box_top =
      native_boiler_.lock()->GetPosition().GetY()
          + native_boiler_.lock()->GetHitBox().GetVerticalShift()
          - native_boiler_.lock()->GetHitBox().GetHeight() / 2;

  long double visible_height =
      boiler_hit_box_top - position_.GetY() + constants::kNpcSize / 2;

  hit_box_.SetHeight(std::min(
      visible_height - picture_above_hit_box_.GetHeight(),
      constants::kNpcHitBoxHeightCoefficient * constants::kNpcSize));

  hit_box_.SetVerticalShift(
      picture_above_hit_box_.GetHeight() + hit_box_.GetHeight() / 2
          - constants::kNpcSize / 2);
}

Point Npc::GetSpawnPos() const {
  return native_boiler_.lock()->GetPosition();
}

void Npc::SetFightingStatus(bool value) {
  is_fighting_ = value;
}

bool Npc::IsFighting() const {
  return is_fighting_;
}

void Npc::CheckFighting() {
  if (is_fighting_ && (tick_counter_ + 1 == constants::kNpcSpeedCoefficient
      * constants::kNumberOfFightingNpc)) {
    is_fighting_ = false;
    tick_counter_ = 0;
  }
}

void Npc::IncrementCounter() {
  ++tick_counter_;
}

void Npc::AttackHero(Hero* hero) const {
  hero->SetHealthPoints(hero->GetHealthPoints() - constants::kNpcDamage);
}
