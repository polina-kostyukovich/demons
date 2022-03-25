#include "vector.h"

#include <cassert>
#include <complex>
#include <iostream>

Vector::Vector(long double x, long double y) : x_(x),
                                               y_(y) {
}
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
  long double sqrt_length = Length();
  x_ /= sqrt_length;
  y_ /= sqrt_length;
}
long double Vector::Length() {
  long double squared_length = (x_ * x_) + (y_ * y_);
  return std::sqrt(squared_length);
}

void Vector::operator=(const Vector& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}
void Vector::operator=(Vector&& vector) {
  x_ = vector.x_;
  y_ = vector.y_;
}

bool Vector::operator==(const Vector& vector) const {
  Vector subtract(*this - vector);
  return subtract.Length() <= constants::kEpsilon;
}
bool Vector::operator!=(const Vector& vector) const {
  return !(*this == vector);
}

void Vector::operator+=(const Vector& vector) {
  x_ += vector.x_;
  y_ += vector.y_;
}
void Vector::operator-=(const Vector& vector) {
  x_ -= vector.x_;
  y_ -= vector.y_;
}
void Vector::operator*=(long double num) {
  x_ *= num;
  y_ *= num;
}
void Vector::operator/=(long double num) {
  if (num == 0) {
    std::cerr << "Zero division\n";
    assert(false);
  }
  x_ /= num;
  y_ /= num;
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
