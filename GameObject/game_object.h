#ifndef GAMEOBJECT_GAME_OBJECT_H_
#define GAMEOBJECT_GAME_OBJECT_H_

#include "../Util/hit_box.h"
#include "../Util/point.h"
#include "../Util/structs.h"

class GameObject {
 public:
  explicit GameObject(const Point& position = Point());

  GameObject(const GameObject& other_object);
  GameObject(GameObject&& other_object);

  GameObject& operator=(const GameObject& other_object);
  GameObject& operator=(GameObject&& other_object);

  void SetPosition(const Point& new_position);
  void SetPositionX(long double new_x);
  void SetPositionY(long double new_y);

  Point GetPosition() const;

  const HitBox& GetHitBox() const;
  const HitBox& GetPictureAboveHitBox() const;

  void SetRenderingLevel(int layer);
  int GetRenderingLevel() const;

  virtual Picture GetPicture() const = 0;

 protected:
  Point position_;
  HitBox hit_box_;
  HitBox picture_above_hit_box_;
  int rendering_level_{0};
};

#endif  // GAMEOBJECT_GAME_OBJECT_H_
