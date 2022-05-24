#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include <string>
#include <vector>

#include "creature.h"
#include "../Util/structs.h"
#include "../Util/vector.h"
#include "../Map/map.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position = Point());

  static void LoadPictures();

  void Update(const Point& target_position, const Map& map);
  bool CanMove(const Point& new_position, const Map& map);
  void Move(const Vector2D& direction);

  Picture GetPicture() const;

  int GetCounter() const;
  void SetCounter(int counter);

 private:
  static void InputPictures(std::string);

 private:
  static inline std::vector<QPixmap> pictures_;
  bool is_moving_right_;
  int tick_counter_{0};

  struct ProcessingPoint {
    Point position_;
    long double weight_{0.};

    ProcessingPoint() = default;

    ProcessingPoint(const Point& position, long double weight);

    bool operator==(const ProcessingPoint& second) const;
    bool operator<(const ProcessingPoint& second) const;

    bool operator=(const ProcessingPoint& second);
  };
};

#endif  // GAMEOBJECT_NPC_H_
