#ifndef MAP_MAP_H_
#define MAP_MAP_H_

#include <memory>
#include <utility>
#include <vector>

#include <QPainter>
#include <QPixmap>

#include "../GameObject/boiler.h"
#include "../GameObject/static_object.h"
#include "../Model/constants.h"
#include "../Util/structs.h"

class Map {
 public:
  Map() = default;

  int GetColumnsNumber() const;
  int GetRowsNumber() const;

  void SetObject(const std::shared_ptr<StaticObject>& object, int x, int y);
  const std::shared_ptr<StaticObject>& GetObject(int x, int y) const;
  void RemoveObject(int x, int y);

  void LoadPictures();
  Picture GetPicture() const;

  void SetSize(int width, int height);
  void LoadBoilers();

  const std::vector<std::shared_ptr<StaticObject>>& GetObjects() const;

  std::pair<int, int> GetCellSize() const;
  std::pair<int, int> GetCellCoordinatesOnMap(const Point& point) const;

 private:
  void RemakeVectorOfObjects();

 private:
  int columns_;
  int rows_;
  std::vector<std::vector<std::shared_ptr<StaticObject>>> objects_;
  std::vector<std::shared_ptr<StaticObject>> objects_vector_;
  QPixmap picture_;
  int width_;
  int height_;
};

#endif  // MAP_MAP_H_
