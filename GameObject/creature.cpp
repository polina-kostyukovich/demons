#include "creature.h"

Creature::Creature(const Point& position) : DynamicObject(position) {}

long double Creature::GetHealthPoints() const {
  return health_points_;
}

void Creature::SetHealthPoints(long double health) {
  health_points_ = health;
}
