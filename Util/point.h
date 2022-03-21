#ifndef UTIL_POINT_H_
#define UTIL_POINT_H_

#include <complex>
#include <ostream>
#include <utility>

#include "../Model/constants.h"

class Point {
 public:
    Point();
    Point(long double x, long double y);
    explicit Point(const std::pair<long double, long double>& coords);
    Point(const Point& point);
    Point(Point&& point);

    void Normalize();
    bool IsClose(const Point& another_point);
    static long double Distance(const Point& first, const Point& second);

    bool operator==(const Point& another_point);
    bool operator!=(const Point& another_point);

    Point& operator=(const Point& another_point);
    Point& operator=(Point&& another_point);

    friend Point operator+(const Point& first, const Point& second);
    friend Point operator-(const Point& first, const Point& second);
    Point& operator+=(const Point& another_point);
    Point& operator-=(const Point& another_point);

    friend Point operator+(const Point& point, long double num);
    friend Point operator-(const Point& point, long double num);
    friend Point operator*(const Point& point, long double num);
    friend Point operator/(const Point& point, long double num);
    friend Point operator+(long double num, const Point& point);
    friend Point operator-(long double num, const Point& point);
    friend Point operator*(long double num, const Point& point);
    friend Point operator/(long double num, const Point& point);
    Point& operator+=(long double num);
    Point& operator-=(long double num);
    Point& operator*=(long double num);
    Point& operator/=(long double num);

    friend std::ostream& operator<<(std::ostream& out, const Point& point);

 private:
    long double x_;
    long double y_;
};


#endif  // UTIL_POINT_H_
