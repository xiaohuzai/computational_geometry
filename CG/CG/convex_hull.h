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
