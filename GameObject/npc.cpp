#include "npc.h"

Npc::Npc(const Point& position) : Creature(position) {}

void Npc::Update(const Point& target_position) {
  const Point& my_position = GetPosition();
  Vector2D direction;
  long double min_distance = constants::kMaxDistance;

  for (long double delta_x = -1;
       delta_x <= 1;
       delta_x += constants::kDirectionStep) {
    for (long double delta_y = -1;
         delta_y <= 1;
         delta_y += constants::kDirectionStep) {
      Vector2D new_direction(delta_x, delta_y);
      new_direction.Normalize();
      long double cur_distance = Point::Distance(my_position + new_direction,
                                                 target_position);
      if (cur_distance < min_distance) {
        direction = new_direction;
        min_distance = cur_distance;
      }
    }
  }

  Move(direction);
}

void Npc::Move(const Vector2D& direction) {
  SetPosition(GetPosition() + direction * constants::kNpcStep);
}
