#pragma once
#include "base_geo_type.h"
#include "geometry_util.h"

class ConvexHull {
public:
	ConvexHull() = default;
	virtual std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const = 0;
	virtual ~ConvexHull() {}
};

/*
* 判断一条边是 extreme edge
	从一群点中找left_edge
	逆时针排序生成
	O(n^3)
*/
class ExtremEdgeAlgo : public ConvexHull {
public:
	ExtremEdgeAlgo() = default;
	virtual ~ExtremEdgeAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
private:
	// 判断p[i]p[j]组成的边是否为左边（其余点都在左边）
	bool to_left_edge(const std::vector<Point2D>& points, int i, int j) const;
};
