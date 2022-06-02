#include "static_object.h"

StaticObject::StaticObject(const Point& position, int width, int height) :
    GameObject(position), width_(width), height_(height) {}

int StaticObject::GetWidth() const {
  return width_;
}

int StaticObject::GetHeight() const {
  return height_;
}
