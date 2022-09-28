#include "convex_hull.h"

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