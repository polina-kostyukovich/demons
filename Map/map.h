#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include <vector>
#include "../GameObject/game_object.h"
#include "../Model/constants.h"

class Map {
 public:
  Map(int window_width, int window_height);
  void SetObject(GameObject* object, int x, int y);
  const GameObject* GetObject(int x, int y) const;

 private:
  int columns_;
  int rows_;
  std::vector<std::vector<GameObject*>> objects_;
};

#endif  // MAP_MAP_H_
