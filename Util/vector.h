#ifndef UTIL_VECTOR_H_
#define UTIL_VECTOR_H_

#include <ostream>

class Vector {
 public:
  Vector() = default;
  Vector(long double x, long double y);
  Vector(const Vector& vector);
  Vector(Vector&&  vector);

  void SetX(long double new_x);
  void SetY(long double new_y);

  long double GetX() const;
  long double GetY() const;

  void Normalize();
  long double Length() const;

  Vector& operator=(const Vector& vector);
  Vector& operator=(Vector&& vector);

  bool operator==(const Vector& vector) const;
  bool operator!=(const Vector& vector) const;

  Vector& operator+=(const Vector& vector);
  Vector& operator-=(const Vector& vector);
  Vector& operator*=(long double num);
  Vector& operator/=(long double num);

  friend Vector operator+(const Vector& first_vector,
                          const Vector& second_vector);
  friend Vector operator-(const Vector& first_vector,
                          const Vector& second_vector);
  friend Vector operator*(const Vector& first_vector,
                          long double num);
  friend Vector operator/(const Vector& first_vector,
                          long double num);
  friend Vector operator*(long double num,
                          const Vector& first_vector);

  friend std::ostream& operator<<(std::ostream& out, const Vector& vector);

 private:
  long double x_{0};
  long double y_{0};
};

#endif  // UTIL_VECTOR_H_
