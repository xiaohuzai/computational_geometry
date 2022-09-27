#include "base_geo_type.h"


double Point2D::x() const { return x_; }
double Point2D::y() const { return y_; }
bool Point2D::operator==(const Point2D& o) {
	return std::fabs(this->x() - o.x()) < std::numeric_limits<double>::epsilon() &&
		std::fabs(this->y() - o.y()) < std::numeric_limits<double>::epsilon();
}
bool Point2D::operator!=(const Point2D& o) {
	return !(*this == o);
}

Point2D operator-(const Point2D& l, const Point2D& r) {
	return { l.x() - r.x(), l.y() - r.y() };
}