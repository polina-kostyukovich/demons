#ifndef GAMEOBJECT_NPC_H_
#define GAMEOBJECT_NPC_H_

#include <memory>
#include <string>
#include <vector>

#include "creature.h"
#include "../GameObject/static_object.h"
#include "../Map/map.h"
#include "../Util/structs.h"
#include "../Util/vector.h"

class Npc : public Creature {
 public:
  explicit Npc(const Point& position,
               const std::weak_ptr<StaticObject>& native_boiler);

  static void LoadPictures();

  void Update(const Point& target_position, const Map& map,
              const std::vector<Npc>& npc_list);
  bool CanMove(const Point& new_position, const Map& map,
               const std::vector<Npc>& npc_list);
  void Move(const Vector2D& direction);

  Picture GetPicture() const;

  int GetCounter() const;
  void SetCounter(int counter);

  Point GetSpawnPos() const;

  bool IsCollidedWithNpc(const std::vector<Npc>& npc_list) const;

 private:
  static void InputPictures(std::string);

  void UpdateFieldsIfBorn(const Point& target_position, const Map& map,
                          const std::vector<Npc>& npc_list);

 private:
  static inline std::vector<QPixmap> pictures_;
  bool is_moving_right_;
  int tick_counter_{0};
  bool is_born_{true};
  std::weak_ptr<StaticObject> native_boiler_;

  struct Cell {
    int x;
    int y;
    long double weight;

    Cell() {
      x = 0;
      y = 0;
      weight = 0;
    }

    Cell(int new_x, int new_y, long double new_weight) :
        x(new_x),
        y(new_y),
        weight(new_weight) {}

    Cell& operator=(const Cell& another_cell) {
      x = another_cell.x;
      y = another_cell.y;
      weight = another_cell.weight;
      return *this;
    }
    bool operator==(const Cell& another_cell) const;
    bool operator<(const Cell& another_cell) const;
  };
};

#endif  // GAMEOBJECT_NPC_H_
