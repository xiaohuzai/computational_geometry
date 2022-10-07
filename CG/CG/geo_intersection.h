#pragma once
#include "base_geo_type.h"
#include <vector>
#include <set>

class BentleyOttmanAlgo {
public:
private:
	static double sweep_line_;
	struct Event_ {
		Point2D p_{};
		bool is_left_{ true };
		int index_{ -1 }; // 所属的segment在sorted_vector中的idx
	};
	struct LineSegment_ {
		int index_{ -1 };
		Point2D left_{};
		Point2D right_{};
		double get_y_by_x() const {
			if (sweep_line_ < left_.x()) {
				return left_.y();
			}
			if (sweep_line_ > right_.x()) {
				return right_.y();
			}
			auto delta = (sweep_line_ - left_.x()) / (right_.x() - left_.x());
			return left_.y() + delta * (right_.y() - left_.y());
		}
		bool operator<(const LineSegment_& l) const {
			auto cur_y = get_y_by_x();
			auto l_y = l.get_y_by_x();
			return cur_y < l_y;
		}
	};
};