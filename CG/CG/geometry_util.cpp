#include "geometry_util.h"

double area2(const Point2D& p, const Point2D& q, const Point2D& s) {
	return p.x() * q.y() - p.y() * q.x() + q.x() * s.y() - q.y() * s.x() + s.x() * p.y() - s.y() * p.x();
}

bool to_left(const Point2D& p, const Point2D& q, const Point2D& s) {
	return area2(p, q, s);
}

bool get_intersect(const Point2D& p0, const Point2D& p1, const Point2D& q0, const Point2D& q1, Point2D& res) {
	auto p_x = p1.x() - p0.x();
	auto p_y = p1.y() - p0.y();
	auto q_x = q1.x() - q0.x();
	auto q_y = q1.y() - q0.y();
	auto p_t = (q_x * (p0.y() - q0.y()) - q_y * (p0.x() - q0.x())) / (-q_x * p_y + p_x * q_y);
	auto q_u = (-p_y * (p0.x() - q0.x()) + p_x * (p0.y() - q0.y())) / (-q_x * p_y + p_x * q_y);
	if (p_t >= 0 && p_t <= 1 && q_u >= 0 && q_u <= 1) {
		res = Point2D{ p0.x() + p_t * p_x, p0.y() + p_t * p_y };
		return true;
	}
	return false;
}

bool counter_clockwise(const Point2D& p, const Point2D& q, const Point2D& r) {
	return (q.x() - p.x()) * (r.y() - p.y()) - (q.y() - p.y()) * (r.x() - p.x()) > 0;
}

bool in_triangle(const Point2D& p, const Point2D& q, const Point2D& r, const Point2D& s) {
	if (counter_clockwise(p, q, r)) {
		if (to_left(p, q, s) && to_left(q, r, s) && to_left(r, p, s)) {
			return true;
		}
	} else {
		if (to_left(r, q, s) && to_left(q, p, s) && to_left(p, r, s)) {
			return true;
		}
	}
	return false;
}

bool in_convex_polygon(const std::vector<Point2D>& extrem_points, const Point2D& pt) {
	if (extrem_points.size() < 3U) {
		return false;
	}
	const auto &pt0 = extrem_points[0];
	const auto &pt1 = extrem_points[1];
	for (auto itr = extrem_points.cbegin() + 1; itr != extrem_points.cend(); ++itr) {
		if (in_triangle(pt0, pt1, *itr, pt)) {
			return true;
		}
	}
	return false;
}

