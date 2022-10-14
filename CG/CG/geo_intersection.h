#pragma once
#include "base_geo_type.h"
#include <vector>

class BentleyOttmanAlgo {
public:
	std::vector<Point2D> get_intersection(const std::vector<Segment2D>& segs);
private:
	struct Event_ {
		Event_(const Point2D& p, char type, const std::pair<int, int>& index)
			:p_(p), type_(type), index_(index) {}
		Point2D p_{};
		char type_{ 0 }; // 0: left, 1: right, 2:intersect
		std::pair<int, int>index_{ -1, -1 }; // 所属的Segment2D的index，如果是intersection，则从高到低排
		bool operator<(const Event_& e) const { return p_.x() < e.p_.x(); }
		bool operator>(const Event_& e) const { return p_.x() > e.p_.x(); }
	};
	struct LineSegment_ {
		int index_{ -1 };
		Segment2D segment_{};
		double get_y_by_x(double x) const {
			if (x < segment_.start().x()) { return segment_.start().y(); }
			if (x > segment_.end().x()) { return segment_.end().y(); }
			auto delta = (x - segment_.start().x()) / (segment_.end().x() - segment_.start().x());
			return segment_.start().y() + delta * (segment_.end().y() - segment_.start().y());
		}
	};
};