# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 18:06:27 2022

@author: yan.huang
"""
from typing import List
import math


class Point2D:
    def __init__(self, x=0.0, y=0.0):
        self.x_ = x
        self.y_ = y

    def __repr__(self):
        return "Point2D(" + str(self.x_) + ", " + str(self.y_) + ")"

    def __eq__(self, o) -> bool:
        if isinstance(o, Point2D):
            return math.isclose(self.x_, o.x_) and math.isclose(self.y_, o.y_)
        return False

    def __sub__(self, o):
        if isinstance(o, Point2D):
            return Point2D(self.x_ - o.x_, self.y_ - o.y_)
        raise Exception('type error')


class Interval:
    def __init__(self, lower=0.0, upper=0.0) -> None:
        self.lower_ = lower
        self.upper_ = upper

    def __repr__(self) -> str:
        return "Interval(" + str(self.lower_) + ", " + str(self.upper_) + ")"


class Vector2D:
    def __init__(self, x=0.0, y=0.0):
        self.x_ = x
        self.y_ = y

    @classmethod
    def consByPoint2D(self, p: Point2D):
        return self(p.x_, p.y_)

    def __repr__(self):
        return "Vector2D(" + str(self.x_) + ", " + str(self.y_) + ")"

    def __eq__(self, o) -> bool:
        if isinstance(o, Vector2D):
            return math.isclose(self.x_, o.x_) and math.isclose(self.y_, o.y_)
        return False


def area2(p: Point2D, q: Point2D, s: Point2D) -> float:
    '''
      s是否在pq左侧
      使用行列式
      2*S = | p.x_  p.y_  1 |
            | q.x_  q.y_  1 |
            | s.x_  s.y_  1 |
    '''
    return p.x_ * q.y_ - p.y_ * q.x_ + q.x_ * s.y_ - q.y_ * s.x_ + s.x_ * p.y_ - s.y_ * p.x_


def toLeft(p: Point2D, q: Point2D, s: Point2D) -> bool:
    '''
    求s是否在pq向量的左边
    '''
    return area2(p, q, s) > 0


def getLineIntersection(p0: Point2D, p1: Point2D, q0: Point2D, q1: Point2D,
                        res: Point2D) -> bool:
    '''
    求p0p1线段和q0q1线段是否有交点
    '''
    p_x = p1.x_ - p0.x_
    p_y = p1.y_ - p0.y_
    q_x = q1.x_ - q0.x_
    q_y = q1.y_ - q0.y_
    p_t = (q_x * (p0.y_ - q0.y_) - q_y * (p0.x_ - q0.x_)) / \
        (-q_x * p_y + p_x * q_y)
    q_u = (-p_y * (p0.x_ - q0.x_) + p_x * (p0.y_ - q0.y_)) / \
        (-q_x * p_y + p_x * q_y)
    if p_t >= 0 and p_t <= 1 and q_u >= 0 and q_u <= 1:
        res = Point2D(p0.x_ + p_t * p_x, p0.y_ + p_t * p_y)
        return True
    return False


def counterclockwise(p: Point2D, q: Point2D, r: Point2D) -> bool:
    '''
    判断p, q, r是否是逆时针排列, 求叉积
    '''
    return (q.x_ - p.x_) * (r.y_ - p.y_) - (q.y_ - p.y_) * (r.x_ - p.x_) > 0


def inTriangle(p: Point2D, q: Point2D, r: Point2D, s: Point2D) -> bool:
    '''
    判断s是否在p、q、r组成的三角形内
    '''
    if counterclockwise(p, q, r):
        if toLeft(p, q, s) and toLeft(q, r, s) and toLeft(r, p, s):
            return True
    else:
        if toLeft(r, q, s) and toLeft(q, p, s) and toLeft(p, r, s):
            return True
    return False


def inConvexPolygon(extreme_points: List[Point2D], pt: Point2D) -> bool:
    pt_size = len(extreme_points)
    if pt_size < 3:
        return False
    pt0 = extreme_points[0]
    pt1 = extreme_points[1]
    in_triangle = False
    for i in range(2, pt_size):
        if inTriangle(pt0, pt1, extreme_points[i], pt):
            in_triangle = True
            break
    return in_triangle


def calcAngle(v: Vector2D) -> float:
    '''
    float
        0~2pi.
    '''
    res = math.atan2(v.y_, v.x_)
    if res < 0:
        res = 2 * math.pi + res
    return res


def calcAngleDiff(v1: Vector2D, v2: Vector2D) -> float:
    '''
    计算v1 v2的夹角

    Returns
    -------
    float
        + v2在v1右边.
        - v2在v1左边
    '''

    return calcAngle(v1) - calcAngle(v2)


def LTL(points: List[Point2D]) -> int:
    '''
    寻找the lowest-then-leftmost point
    Returns
    -------
    int
        LTL idx.
    '''
    ltl_idx = 0
    for i in range(1, len(points)):
        if points[i].y_ < points[ltl_idx].y_ or (
                points[i].y_ == points[ltl_idx].y_
                and points[i].x_ < points[ltl_idx].x_):
            ltl_idx = i
    return ltl_idx


def sortByAngle(p: Point2D, points: List[Point2D]) -> List[Point2D]:
    return sorted(points,
                  key=lambda pt: calcAngle(Vector2D.consByPoint2D(pt - p)))


def nextStepPt(points: List[Point2D], i: int, step: int) -> Point2D:
    '''
    找i点接下来step步长的点，step可正可负
    '''
    pts_size = len(points)
    if pts_size == 0:
        return Point2D()
    return points[(i + step) % pts_size]