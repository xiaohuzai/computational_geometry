#pragma once
#include "base_geo_type.h"
#include <vector>

template<typename T>
bool almost_equal(T l, T r) {
	return std::fabs(l - r) < std::numeric_limits<T>::epsilon();
}

/*
	  s�Ƿ���pq���
	  ʹ������ʽ
	  2*S = | p.x_  p.y_  1 |
			| q.x_  q.y_  1 |
			| s.x_  s.y_  1 |
*/
double area2(const Point2D& p, const Point2D& q, const Point2D& s);

bool to_left(const Point2D& p, const Point2D& q, const Point2D& s);

/*
	��p0p1�߶κ�q0q1�߶��Ƿ��н���
	p0 + t*p == q0 + u*q, p��qΪ����
*/
bool get_intersect(const Point2D& p0, const Point2D& p1, const Point2D& q0, const Point2D& q1, Point2D& res);

/*
* �ж�p,q,s�Ƿ�����ʱ�����У�����
*/
bool counter_clockwise(const Point2D& p, const Point2D& q, const Point2D& r);

/*
* �ж�s�Ƿ���p��q��r��ɵ���������
*/
bool in_triangle(const Point2D& p, const Point2D& q, const Point2D& r, const Point2D& s);

/*
* �ж�pt�Ƿ�����extrem_points��ɵ�͹����
*/
bool in_convex_polygon(const std::vector<Point2D>& extrem_points, const Point2D& pt);

/*
* ����һ�������ĽǶ�
* 0~2pi
*/
double calc_angle(const Vector2D& v);

std::vector<Point2D> sort_by_angle(const Point2D& p, const std::vector<Point2D>& points);

/*
* ����v1 v2�ļн�
* Returns
	-------
	float
		+ v2��v1�ұ�.
		- v2��v1���
*/
double calc_angle_diff(const Vector2D& v1, const Vector2D& v2);

/*
* Ѱ��the lowest-then-leftmost point
* Returns
	-------
	int
		LTL idx.
*/
int ltl_pt(const std::vector<Point2D>& points);
