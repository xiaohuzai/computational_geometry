#pragma once
#include "base_geo_type.h"
#include <vector>
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

bool in_convex_polygon(const std::vector<Point2D> &extrem_points, const Point2D &pt);