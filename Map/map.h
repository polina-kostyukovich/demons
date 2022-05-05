#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include <memory>
#include <vector>

#include <QPainter>
#include <QPixmap>

#include "../GameObject/boiler.h"
#include "../GameObject/game_object.h"
#include "../Model/constants.h"
#include "../Util/structs.h"

class Map {
 public:
  Map();

  int GetColumnsNumber() const;
  int GetRowsNumber() const;

  void SetObject(const std::shared_ptr<GameObject>& object, int x, int y);
  const std::shared_ptr<GameObject>& GetObject(int x, int y) const;
  void RemoveObject(int x, int y);

  void LoadPictures();
  Picture GetPicture() const;

  void SetSize(int width, int height);
  void LoadBoilers();

  const std::vector<std::shared_ptr<GameObject>>& GetObjects() const;

 private:
  void RemakeVectorOfObjects();

 private:
  int columns_;
  int rows_;
  std::vector<std::vector<std::shared_ptr<GameObject>>> objects_;
  std::vector<std::shared_ptr<GameObject>> objects_vector_;
  QPixmap picture_;
  int width_;
  int height_;
};

#endif  // MAP_MAP_H_
