#include "geometry_util.h"
#include <algorithm>

double area2(const Point2D& p, const Point2D& q, const Point2D& s) {
	return p.x() * q.y() - p.y() * q.x() + q.x() * s.y() - q.y() * s.x() + s.x() * p.y() - s.y() * p.x();
}

bool to_left(const Point2D& p, const Point2D& q, const Point2D& s) {
	return area2(p, q, s) > 0;
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
	}
	else {
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
	const auto& pt0 = extrem_points[0];
	const auto& pt1 = extrem_points[1];
	for (auto itr = extrem_points.cbegin() + 1; itr != extrem_points.cend(); ++itr) {
		if (in_triangle(pt0, pt1, *itr, pt)) {
			return true;
		}
	}
	return false;
}

double calc_angle(const Vector2D& v) {
	auto res = std::atan2(v.y(), v.x());
	if (res < 0) {
		res = 2 * PI + res;
	}
	return res;
}

std::vector<Point2D> sort_by_angle(const Point2D& p, const std::vector<Point2D>& points) {
	std::vector<Point2D> new_pts = points;
	std::sort(new_pts.begin(), new_pts.end(), [&](const auto& l, const auto& r) {
		return to_left(p, l, r);
		});
	return new_pts;
}

double calc_angle_diff(const Vector2D& v1, const Vector2D& v2) {
	return calc_angle(v1) - calc_angle(v2);
}

int ltl_pt(const std::vector<Point2D>& points) {
	int ltl_idx = 0;
	for (size_t i = 0; i < points.size(); ++i) {
		if (points[i].y() < points[ltl_idx].y() ||
			(almost_equal(points[i].y(), points[ltl_idx].y()) &&
				points[i].x() < points[ltl_idx].x())) {
			ltl_idx = i;
		}
	}
	return ltl_idx;
}

Point2D next_step_pt(const std::vector<Point2D>& points, size_t idx, int step) {
	if (points.empty()) {
		return {};
	}
	auto size = points.size();
	return points[(idx + step + size) % size];
}