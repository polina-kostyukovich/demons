#include "point.h"

#include <cassert>
#include <complex>
#include <iostream>

Point::Point(long double x, long double y) {
    x_ = x;
    y_ = y;
}
Point::Point(const Point& point) {
    x_ = point.x_;
    y_ = point.y_;
}
Point::Point(Point&& point) {
    x_ = point.x_;
    y_ = point.y_;
}

long double Point::Distance(const Point& first, const Point& second) {
    long double delta_x = second.x_ - first.x_;
    long double delta_y = second.y_ - first.y_;
    long double squared_distance = (delta_x * delta_x) + (delta_y * delta_y);
    return std::sqrt(squared_distance);
}
bool Point::IsClose(const Point& another_point) const {
    return (Distance(*this, another_point) <= constants::kClose);
}

void Point::SetX(long double new_x) {
    x_ = new_x;
}
void Point::SetY(long double new_y) {
    y_ = new_y;
}

long double Point::GetX() const {
    return x_;
}
long double Point::GetY() const {
    return y_;
}

bool Point::operator==(const Point& another_point) const {
    return (Distance(*this, another_point) <= constants::kEpsilon);
}
bool Point::operator!=(const Point &another_point) const {
    return !(*this == another_point);
}

Point& Point::operator=(const Point& another_point) {
    x_ = another_point.x_;
    y_ = another_point.y_;
    return *this;
}
Point& Point::operator=(Point&& another_point) {
    x_ = another_point.x_;
    y_ = another_point.y_;
    return *this;
}

Point operator+(const Point& first, const Point& second) {
    Point result(first);
    result += second;
    return result;
}
Point operator-(const Point& first, const Point& second) {
    Point result(first);
    result -= second;
    return result;
}
Point& Point::operator+=(const Point& another_point) {
    x_ += another_point.x_;
    y_ += another_point.y_;
    return *this;
}
Point& Point::operator-=(const Point& another_point) {
    x_ -= another_point.x_;
    y_ -= another_point.y_;
    return *this;
}

Point operator*(const Point& point, long double num) {
    Point result(point);
    result *= num;
    return result;
}
Point operator/(const Point& point, long double num) {
    Point result(point);
    result /= num;
    return result;
}
Point operator*(long double num, const Point& point) {
    return (point * num);
}
Point& Point::operator*=(long double num) {
    x_ *= num;
    y_ *= num;
    return *this;
}
Point& Point::operator/=(long double num) {
    if (num == 0) {
        std::cerr << "Zero division\n";
        assert(false);
    }
    x_ /= num;
    y_ /= num;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Point &point) {
    out << "Point: " << point.x_ << " " << point.y_ << "\n";
    return out;
}
