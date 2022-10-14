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
* �ж�һ������ extreme edge
	��һȺ������left_edge
	��ʱ����������
	O(n^3)
*/
class ExtremEdgeAlgo : public ConvexHull {
public:
	ExtremEdgeAlgo() = default;
	virtual ~ExtremEdgeAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
private:
	// �ж�p[i]p[j]��ɵı��Ƿ�Ϊ��ߣ�����㶼����ߣ�
	bool to_left_edge(const std::vector<Point2D>& points, int i, int j) const;
};

/*
* O(n2)
*�����¼ӵĵ��pattern����̬ά��extrem points����
*/
class IncrementalAlgo : public ConvexHull {
public:
	IncrementalAlgo() = default;
	virtual ~IncrementalAlgo() {}
	std::vector<Point2D> gen_extrem_points(const std::vector<Point2D>& points) const override final;
private:
	// �ҳ�s->points[idx]������pattern�����ж�i��prev��next���s->points[idx]����������
	std::pair<bool, bool> vertex_pattern(const std::vector<Point2D>& points, const Point2D& s, size_t idx) const;
};

/*
* O(nh)
* ���ҵ�ltl��,Ȼ����ʱ�밴�սǶ�����С�Ƕ���ת�ĵ㣬��Ϊextreme_point
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