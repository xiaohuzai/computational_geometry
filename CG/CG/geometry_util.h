#pragma once
#include "base_geo_type.h"
#include <vector>

template<typename T>
bool almost_equal(T l, T r) {
	return std::fabs(l - r) < std::numeric_limits<T>::epsilon();
}

/*
	  s是否在pq左侧
	  使用行列式
	  2*S = | p.x_  p.y_  1 |
			| q.x_  q.y_  1 |
			| s.x_  s.y_  1 |
*/
double area2(const Point2D& p, const Point2D& q, const Point2D& s);

bool to_left(const Point2D& p, const Point2D& q, const Point2D& s);

/*
	求p0p1线段和q0q1线段是否有交点
	p0 + t*p == q0 + u*q, p、q为向量
*/
bool get_intersect(const Point2D& p0, const Point2D& p1, const Point2D& q0, const Point2D& q1, Point2D& res);

/*
* 判断p,q,s是否是逆时针排列，求叉积
*/
bool counter_clockwise(const Point2D& p, const Point2D& q, const Point2D& r);

/*
* 判断s是否在p、q、r组成的三角形内
*/
bool in_triangle(const Point2D& p, const Point2D& q, const Point2D& r, const Point2D& s);

/*
* 判断pt是否在以extrem_points组成的凸包内
*/
bool in_convex_polygon(const std::vector<Point2D>& extrem_points, const Point2D& pt);

/*
* 计算一个向量的角度
* 0~2pi
*/
double calc_angle(const Vector2D& v);

std::vector<Point2D> sort_by_angle(const Point2D& p, const std::vector<Point2D>& points);

/*
* 计算v1 v2的夹角
* Returns
	-------
	float
		+ v2在v1右边.
		- v2在v1左边
*/
double calc_angle_diff(const Vector2D& v1, const Vector2D& v2);

/*
* 寻找the lowest-then-leftmost point
* Returns
	-------
	int
		LTL idx.
*/
int ltl_pt(const std::vector<Point2D>& points);
