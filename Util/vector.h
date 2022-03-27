#ifndef UTIL_VECTOR_H_
#define UTIL_VECTOR_H_

#include <ostream>

class Vector2D {
 public:
  Vector2D() = default;
  Vector2D(long double x, long double y);
  Vector2D(const Vector2D& vector);
  Vector2D(Vector2D&&  vector);

  void SetX(long double new_x);
  void SetY(long double new_y);

  long double GetX() const;
  long double GetY() const;

  void Normalize();
  long double Length() const;

  Vector2D& operator=(const Vector2D& vector);
  Vector2D& operator=(Vector2D&& vector);

  bool operator==(const Vector2D& vector) const;
  bool operator!=(const Vector2D& vector) const;

  Vector2D& operator+=(const Vector2D& vector);
  Vector2D& operator-=(const Vector2D& vector);
  Vector2D& operator*=(long double num);
  Vector2D& operator/=(long double num);

  friend Vector2D operator+(const Vector2D& first_vector,
                          const Vector2D& second_vector);
  friend Vector2D operator-(const Vector2D& first_vector,
                          const Vector2D& second_vector);
  friend Vector2D operator*(const Vector2D& first_vector,
                          long double num);
  friend Vector2D operator/(const Vector2D& first_vector,
                          long double num);
  friend Vector2D operator*(long double num,
                          const Vector2D& first_vector);

  friend std::ostream& operator<<(std::ostream& out, const Vector2D& vector);

 private:
  long double x_{0.};
  long double y_{0.};
};

#endif  // UTIL_VECTOR_H_
