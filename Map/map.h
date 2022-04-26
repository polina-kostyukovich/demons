#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include <memory>
#include <vector>
#include <QPainter>
#include <QPixmap>

#include "../GameObject/game_object.h"
#include "../Model/constants.h"
#include "../Util/structs.h"

class Map {
 public:
  Map(int window_width, int window_height);

  int GetColumnsNumber() const;
  int GetRowsNumber() const;

  void SetObject(std::unique_ptr<GameObject>&& object, int x, int y);
  const std::unique_ptr<GameObject>& GetObject(int x, int y) const;
  void RemoveObject(int x, int y);

  void LoadPictures();
  Animation GetAnimation(int counter) const;

  void SetMap(QPixmap pixmap);

  void MakeMap(int width, int height);

 private:
  int columns_;
  int rows_;
  std::vector<std::vector<std::unique_ptr<GameObject>>> objects_;
  QPixmap map;
  int width_;
  int height_;
};

#endif  // MAP_MAP_H_
