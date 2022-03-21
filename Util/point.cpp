#include "point.h"

Point::Point() {
    x_ = 0;
    y_ = 0;
}
Point::Point(long double x, long double y) {
    x_ = x;
    y_ = y;
}
Point::Point(const std::pair<long double, long double>& coords) {
    x_ = coords.first;
    y_ = coords.second;
}
Point::Point(const Point& point) {
    x_ = point.x_;
    y_ = point.y_;
}
Point::Point(Point&& point) {
    x_ = point.x_;
    y_ = point.y_;
}

bool Point::operator==(const Point& another_point) {
    if (x_ == another_point.x_ && y_ == another_point.y_) {
        return true;
    }
    return false;
}
bool Point::operator!=(const Point &another_point) {
    if (x_ == another_point.x_ && y_ == another_point.y_) {
        return false;
    }
    return true;
}

Point& Point::operator=(const Point& another_point) {
    x_ = another_point.x_;
    y_ = another_point.y_;
    return *this;
}
Point& Point::operator=(Point&& another_point) {
    if (another_point == *this) {
        return *this;
    }
    x_ = another_point.x_;
    y_ = another_point.y_;
    return *this;
}

long double Point::Distance(const Point& first, const Point& second) {
    long double delta_x = second.x_ - first.x_;
    long double delta_y = second.y_ - first.y_;
    long double squared_distance = (delta_x * delta_x) + (delta_y * delta_y);
    return std::sqrt(squared_distance);
}
bool Point::IsClose(const Point& another_point) {
    return (Point::Distance(*this, another_point) <= constants::epsilon);
}
void Point::Normalize() {
    long double sum = x_ + y_;
    (*this) /= sum;
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

Point operator+(const Point& point, long double num) {
    Point result(point);
    result += num;
    return result;
}
Point operator-(const Point& point, long double num) {
    Point result(point);
    result -= num;
    return result;
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
Point operator+(long double num, const Point& point) {
    return (point + num);
}
Point operator-(long double num, const Point& point) {
    return (point - num);
}
Point operator*(long double num, const Point& point) {
    return (point * num);
}
Point operator/(long double num, const Point& point) {
    return (point / num);
}
Point& Point::operator+=(long double num) {
    x_ += num;
    y_ += num;
    return *this;
}
Point& Point::operator-=(long double num) {
    x_ -= num;
    y_ -= num;
    return *this;
}
Point& Point::operator*=(long double num) {
    x_ *= num;
    y_ *= num;
    return *this;
}
Point& Point::operator/=(long double num) {
    if (num == 0) {
        throw "Bad division";
        return *this;
    }
    x_ /= num;
    y_ /= num;
    return *this;
}

std::ostream& operator<<(std::ostream& out, const Point &point) {
    out << "Point: " << point.x_ << " " << point.y_ << "\n";
    return out;
}
