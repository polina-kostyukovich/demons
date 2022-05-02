#include "vector.h"

#include <cassert>
#include <complex>
#include <iostream>

#include "../Model/constants.h"

Vector2D::Vector2D(long double x, long double y) : x_(x),
                                               y_(y) {}
Vector2D::Vector2D(const Vector2D& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}

Vector2D::Vector2D(Vector2D&& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}

Vector2D::Vector2D(const Point& a, const Point& b) {
  x_ = b.GetX() - a.GetX();
  y_ = b.GetY() - a.GetY();
}

void Vector2D::SetX(long double new_x) {
  x_ = new_x;
}

void Vector2D::SetY(long double new_y) {
  y_ = new_y;
}

long double Vector2D::GetX() const {
  return x_;
}

long double Vector2D::GetY() const {
  return y_;
}

void Vector2D::Normalize() {
  if (x_ == 0 && y_ == 0) {
    return;
  }
  long double old_length = Length();
  x_ /= old_length;
  y_ /= old_length;
}

long double Vector2D::Length() const {
  long double squared_length = (x_ * x_) + (y_ * y_);
  return std::sqrt(squared_length);
}

Vector2D& Vector2D::operator=(const Vector2D& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
  return *this;
}

Vector2D& Vector2D::operator=(Vector2D&& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
  return *this;
}

bool Vector2D::operator==(const Vector2D& vector) const {
  return std::abs(x_ - vector.x_) <= constants::kEpsilon &&
         std::abs(y_ - vector.y_) <= constants::kEpsilon;
}

bool Vector2D::operator!=(const Vector2D& vector) const {
  return !(*this == vector);
}

Vector2D& Vector2D::operator+=(const Vector2D& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  return *this;
}

Vector2D& Vector2D::operator*=(long double num) {
  x_ *= num;
  y_ *= num;
  return *this;
}

Vector2D& Vector2D::operator/=(long double num) {
  if (num == 0) {
    std::cerr << "Zero division\n";
    assert(false);
  }
  x_ /= num;
  y_ /= num;
  return *this;
}

Vector2D operator+(const Vector2D& first_vector,
                   const Vector2D& second_vector) {
  Vector2D result(first_vector);
  result += second_vector;
  return result;
}

Vector2D operator-(const Vector2D& first_vector,
                   const Vector2D& second_vector) {
  Vector2D result(first_vector);
  result -= second_vector;
  return result;
}

Vector2D operator*(const Vector2D& vector, long double num) {
  Vector2D result(vector);
  result *= num;
  return result;
}

Vector2D operator/(const Vector2D& vector, long double num) {
  Vector2D result(vector);
  result /= num;
  return result;
}

Vector2D operator*(long double num, const Vector2D& vector) {
  return vector * num;
}

Point operator+(const Point& point, const Vector2D& vector) {
  Point result(point);
  result.SetX(result.GetX() + vector.x_);
  result.SetY(result.GetY() + vector.y_);
  return result;
}

Point operator+(const Vector2D& vector, const Point& point) {
  return point + vector;
}

Point operator-(const Point& point, const Vector2D& vector) {
  Vector2D new_vector = vector * -1;
  return point + new_vector;
}

std::ostream& operator<<(std::ostream& out, const Vector2D& vector) {
  out << "Vector: (" << vector.x_ << ", " << vector.y_ << ")\n";
  return out;
}
