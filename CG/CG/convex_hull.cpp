#include "convex_hull.h"
#include <deque>
#include <algorithm>
#include <CGAL/convex_hull_2.h>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>

std::vector<Point2D> ExtremEdgeAlgo::gen_extrem_points(const std::vector<Point2D>& points) const {
	auto pts_size = points.size();
	if (pts_size <= 2) {
		return {};
	}
	auto res = std::vector<Point2D>{};
	res.reserve(pts_size);
	auto marked = std::vector<bool>(pts_size, false);
	int convex_vertex_idx = -1;
	bool find_first_vertex = false;
	for (int i = 0; i < pts_size; ++i) { // O(n)
		for (int j = 0; j < pts_size; ++j) { // O(n)
			if (i != j && to_left_edge(points, i, j)) { // O(n)
				marked[i] = true;
				res.push_back(points[i]);
				convex_vertex_idx = j;
				find_first_vertex = true;
				break;
			}
		}
		if (find_first_vertex) {
			break;
		}
	}
	while (true) { // O(n)
		bool found = false;
		for (int i = 0; i < pts_size; ++i) { // O(n)
			if (!marked[i] && i != convex_vertex_idx && to_left_edge(points, convex_vertex_idx, i)) {
				marked[convex_vertex_idx] = true;
				res.push_back(points[convex_vertex_idx]);
				convex_vertex_idx = i;
				found = true;
				break;
			}
		}
		if (!found) {
			break;
		}
	}
	res.push_back(points[convex_vertex_idx]);
	return res;
}

bool ExtremEdgeAlgo::to_left_edge(const std::vector<Point2D>& points, int i, int j) const {
	auto pt_size = points.size();
	if (i < 0 || i >= pt_size || j < 0 || j >= pt_size) {
		return false;
	}
	for (int k = 0; k < pt_size; ++k) {
		if (k != i && k != j && to_left(points[i], points[j], points[k])) {
			return false;
		}
	}
	return true;
}

std::vector<Point2D> IncrementalAlgo::gen_extrem_points(const std::vector<Point2D>& points) const {
	if (points.size() < 2U) {
		return points;
	}
	auto res = std::vector<Point2D>{ points[0], points[1] };
	// 找到一个逆时针排序
	auto itr = std::find_if(points.cbegin() + 2, points.cend(), [&](const auto& p) {return counter_clockwise(res[0], res[1], p); });
	if (itr == points.cend()) {
		std::reverse(res.begin(), res.end());
		itr = std::find_if(points.cbegin() + 2, points.cend(), [&](const auto& p) {return counter_clockwise(res[0], res[1], p); });
		if (itr == points.cend()) {
			return points;
		}
	}
	res.push_back(*itr);
	for (size_t i = 0; i < points.size(); ++i) {
		int t_idx = -1;  // 所有的点都points[idx]->points[t_idx]的右边
		int s_idx = -1;  // 所有的点都points[idx]->points[t_idx]的左边
		for (size_t j = 0; j < res.size(); ++j) {
			if (points[i] == res[j] || (t_idx >= 0 && s_idx >= 0)) {
				break;
			}
			auto pattern = vertex_pattern(res, points[i], j);
			if (!pattern.first && !pattern.second && t_idx < 0) {
				t_idx = j;
			}
			if (pattern.first && pattern.second && s_idx < 0) {
				s_idx = j;
			}
		}
		if (t_idx < 0 || s_idx < 0) {
			continue;
		}
		auto new_res = std::vector<Point2D>{};
		if (s_idx > t_idx) {
			new_res.insert(new_res.end(), res.cbegin(), res.cbegin() + t_idx + 1);
			new_res.push_back(points[i]);
			new_res.insert(new_res.end(), res.cbegin() + s_idx, res.cend());
		}
		else {
			new_res.insert(new_res.end(), res.cbegin() + s_idx, res.cbegin() + t_idx + 1);
			new_res.push_back(points[i]);
		}
		res = new_res;
	}
	return res;
}

std::pair<bool, bool> IncrementalAlgo::vertex_pattern(const std::vector<Point2D>& points, const Point2D& s, size_t idx) const {
	auto prev_pt = next_step_pt(points, idx, -1);
	auto next_pt = next_step_pt(points, idx, 1);
	auto cur_pt = points[idx];
	return { to_left(s, cur_pt, prev_pt), to_left(s, cur_pt, next_pt) };
}

std::vector<Point2D> JarvisMarchAlgo::gen_extrem_points(const std::vector<Point2D>& points) const {
	auto marked = std::vector<bool>(points.size(), false);
	auto res = std::vector<Point2D>{};
	auto ltl_idx = ltl_pt(points);
	auto last_idx = ltl_idx;
	res.push_back(points[ltl_idx]);
	marked[ltl_idx] = true;
	while (true) {
		auto cur_idx = -1;
		for (int i = 1; i < points.size(); ++i) {
			if (i == last_idx) {
				continue;
			}
			if (cur_idx == -1 || to_left(points[last_idx], points[cur_idx], points[i])) {
				cur_idx = i;
			}
		}
		if (cur_idx == -1 || marked[cur_idx]) {
			break;
		}
		marked[cur_idx] = true;
		res.push_back(points[cur_idx]);
		last_idx = cur_idx;
	}
	return res;
}

std::vector<Point2D> GrahamScaneAlgo::gen_extrem_points(const std::vector<Point2D>& points) const {
	if (points.size() <= 3U) {
		return points;
	}
	auto res = std::deque<Point2D>{};
	auto sorted_points = std::deque<Point2D>{};
	auto ltl_idx = ltl_pt(points);
	res.push_back(points[ltl_idx]);
	if (ltl_idx == points.size() - 1) {
		sorted_points.insert(sorted_points.end(), points.cbegin(), points.cend() - 1);
	}
	else {
		sorted_points.insert(sorted_points.end(), points.cbegin(), points.cbegin() + ltl_idx);
		sorted_points.insert(sorted_points.end(), points.cbegin() + ltl_idx + 1, points.cend());
	}
	std::sort(sorted_points.begin(), sorted_points.end(), [&](const auto& l, const auto& r) {
		return to_left(points[ltl_idx], l, r);
		});
	while (!sorted_points.empty()) {
		const auto& sorted_points_top = sorted_points[0];
		while (res.size() > 1U) {
			const auto& res_top = res[0];
			const auto& res_second = res[1];
			if (to_left(res_second, res_top, sorted_points_top)) {
				res.push_front(sorted_points_top);
				break;
			}
			else {
				res.pop_front();
			}
		}
		if (res.size() < 2U) {
			res.push_front(sorted_points_top);
		}
		sorted_points.pop_front();
	}
	auto res_vec = std::vector<Point2D>(res.cbegin(), res.cend());
	std::reverse(res_vec.begin(), res_vec.end());
	return res_vec;
}

std::vector<Point2D> gen_extrem_points_by_cgal(const std::vector<Point2D>& points) {
	using Point_2 = CGAL::Exact_predicates_inexact_constructions_kernel::Point_2;
	auto cgal_pts_tmp = std::vector<Point_2>{};
	cgal_pts_tmp.reserve(points.size());
	std::transform(points.cbegin(), points.cend(), std::back_inserter(cgal_pts_tmp), [](const auto& p) {
		return Point_2{ p.x(), p.y() };
		});
	auto res_tmp = std::vector<Point_2>{};
	CGAL::ch_graham_andrew(cgal_pts_tmp.cbegin(), cgal_pts_tmp.cend(), std::back_inserter(res_tmp));
	auto res = std::vector<Point2D>{};
	res.reserve(res_tmp.size());
	std::transform(res_tmp.cbegin(), res_tmp.cend(), std::back_inserter(res), [](const auto& p) {
		return Point2D{ p.x(), p.y() };
		});
	return res;
}