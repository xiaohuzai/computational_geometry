#include "base_geo_type.h"

double Point2D::x() const { return x_; }
double Point2D::y() const { return y_; }
bool Point2D::operator==(const Point2D& o) const {
	return almost_equal(this->x(), o.x()) && almost_equal(this->y(), o.y());
}
bool Point2D::operator!=(const Point2D& o) const {
	return !(*this == o);
}

Point2D operator-(const Point2D& l, const Point2D& r) {
	return { l.x() - r.x(), l.y() - r.y() };
}