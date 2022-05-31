#ifndef GAMEOBJECT_BOILER_H_
#define GAMEOBJECT_BOILER_H_

#include <memory>
#include <QPixmap>

#include "static_object.h"
#include "../Util/hit_box.h"
#include "../Util/point.h"
#include "../Util/structs.h"

class Boiler : public StaticObject {
 public:
  Boiler(const Point& position, int width, int height);

  static void LoadPictures();

  Picture GetPicture() const override;

 private:
  static inline std::unique_ptr<QPixmap> picture_;
  int width_;
  int height_;
};

#endif  // GAMEOBJECT_BOILER_H_
