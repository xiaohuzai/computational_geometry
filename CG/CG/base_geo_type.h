#pragma once
#include <ostream>
#include <limits>
const double PI = 2 * std::acos(0.0);

class Point2D {
public:
	Point2D() = default;
	Point2D(double x, double y) : x_(x), y_(y) {}
	double x() const;
	double y() const;
	bool operator==(const Point2D& o);
	bool operator!=(const Point2D& o);
private:
	double x_{ 0.0 };
	double y_{ 0.0 };
};
Point2D operator-(const Point2D& l, const Point2D& r);

using Interval = Point2D;
using Vector2D = Point2D;

class Segment2D {
public:
	Segment2D() = default;
	Segment2D(const Point2D& start, const Point2D& end) : start_(start), end_(end) {}

private:
	Point2D start_{};
	Point2D end_{};
};