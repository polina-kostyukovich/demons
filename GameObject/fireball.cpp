#include "fireball.h"

void Fireball::Move() {
  SetPosition(position_ + direction_ * constants::kFireballSpeed);
}
