#pragma once
#include <ostream>
#include <limits>
const double PI = 2 * std::acos(0.0);
template<typename T>
bool almost_equal(T l, T r) {
	return std::fabs(l - r) < std::numeric_limits<T>::epsilon();
}

class Point2D {
public:
	Point2D() = default;
	Point2D(double x, double y) : x_(x), y_(y) {}
	double x() const;
	double y() const;
	bool operator==(const Point2D& o) const;
	bool operator!=(const Point2D& o) const;
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
	const Point2D& start() const;
	const Point2D& end() const;
private:
	Point2D start_{};
	Point2D end_{};
};