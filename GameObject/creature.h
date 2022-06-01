#ifndef GAMEOBJECT_CREATURE_H_
#define GAMEOBJECT_CREATURE_H_

#include "dynamic_object.h"

class Creature : public DynamicObject {
 public:
  explicit Creature(const Point& position = Point());

  long double GetHealthPoints() const;
  void SetHealthPoints(long double health);

 private:
  long double health_points_{0};
};

#endif  // GAMEOBJECT_CREATURE_H_
