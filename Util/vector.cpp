#include "vector.h"

#include <cassert>
#include <complex>
#include <iostream>

#include "../Model/constants.h"

Vector::Vector(long double x, long double y) : x_(x),
                                               y_(y) {}
Vector::Vector(const Vector& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}

Vector::Vector(Vector&& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}

void Vector::SetX(long double new_x) {
  x_ = new_x;
}

void Vector::SetY(long double new_y) {
  y_ = new_y;
}

long double Vector::GetX() const {
  return x_;
}

long double Vector::GetY() const {
  return y_;
}

void Vector::Normalize() {
  if (x_ == 0 && y_ == 0) {
    return;
  }
  long double old_length = Length();
  x_ /= old_length;
  y_ /= old_length;
}

long double Vector::Length() const {
  long double squared_length = (x_ * x_) + (y_ * y_);
  return std::sqrt(squared_length);
}

Vector& Vector::operator=(const Vector& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
  return *this;
}

Vector& Vector::operator=(Vector&& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
  return *this;
}

bool Vector::operator==(const Vector& vector) const {
  return std::abs(x_ - vector.x_) <= constants::kEpsilon &&
         std::abs(y_ - vector.y_) <= constants::kEpsilon;
}

bool Vector::operator!=(const Vector& vector) const {
  return !(*this == vector);
}

Vector& Vector::operator+=(const Vector& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
  return *this;
}

Vector& Vector::operator-=(const Vector& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
  return *this;
}

Vector& Vector::operator*=(long double num) {
  x_ *= num;
  y_ *= num;
  return *this;
}

Vector& Vector::operator/=(long double num) {
  if (num == 0) {
    std::cerr << "Zero division\n";
    assert(false);
  }
  x_ /= num;
  y_ /= num;
  return *this;
}

Vector operator+(const Vector& first_vector, const Vector& second_vector) {
  Vector result(first_vector);
  result += second_vector;
  return result;
}

Vector operator-(const Vector& first_vector, const Vector& second_vector) {
  Vector result(first_vector);
  result -= second_vector;
  return result;
}

Vector operator*(const Vector& vector, long double num) {
  Vector result(vector);
  result *= num;
  return result;
}

Vector operator/(const Vector& vector, long double num) {
  Vector result(vector);
  result /= num;
  return result;
}

Vector operator*(long double num, const Vector& vector) {
  return vector * num;
}

std::ostream& operator<<(std::ostream& out, const Vector& vector) {
  out << "Vector: (" << vector.x_ << ", " << vector.y_ << ")\n";
  return out;
}
