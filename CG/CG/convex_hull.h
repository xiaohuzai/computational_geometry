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

/*
* O(n2)
*根据新加的点的pattern来动态维护extrem points数组
*/
class IncrementalAlgo : public ConvexHull {
public:
	IncrementalAlgo() = default;
	virtual ~IncrementalAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
private:
	// 找出s->points[idx]向量的pattern，即判断i的prev和next相对s->points[idx]向量的左右
	std::pair<bool, bool> vertex_pattern(const std::vector<Point2D>& points, const Point2D& s, size_t idx) const;
};

/*
* O(nh)
* 先找到ltl点,然后逆时针按照角度找最小角度旋转的点，即为extreme_point
*
*/
class JarvisMarchAlgo : public ConvexHull {
public:
	JarvisMarchAlgo() = default;
	virtual ~JarvisMarchAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
};

/*
*O(nlog(n))
*/
class GrahamScaneAlgo : public ConvexHull {
public:
	GrahamScaneAlgo() = default;
	virtual ~GrahamScaneAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
};

std::vector<Point2D> gen_extrem_points_by_cgal(const std::vector<Point2D>& points);