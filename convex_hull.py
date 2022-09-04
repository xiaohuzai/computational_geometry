# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 20:25:45 2022

@author: yan.huang
"""
import geometry_convex as geo
from typing import List, Tuple
import copy
import sys
import math

# =============================================================================
# Extreme Points Algo. O(n^4)
# =============================================================================


def extremePoint(points: List[geo.Point2D]) -> List[geo.Point2D]:
    '''
    Extreme Point算法
    凸包的点都是极点,使用是否在三角形内判断是否是极点
    O(n^4)复杂度，还要加上额外的排序
    Extreme Points Algo.
    '''
    pt_size = len(points)
    if pt_size < 3:
        return []
    res = []
    not_extreme_idx = set()
    for i in range(0, pt_size):
        for j in range(i+1, pt_size):
            for k in range(j+1, pt_size):
                for t in range(0, pt_size):
                    if t == i or t == j or t == k:
                        continue
                    if geo.inTriangle(points[i], points[j], points[k], points[t]):
                        not_extreme_idx.add(t)
    for i in range(0, pt_size):
        if i not in not_extreme_idx:
            res.append(points[i])
    return res

# =============================================================================
# Extreme Edge Algo. O(n^3)
# =============================================================================


def checkToLeftEdge(points: List[geo.Point2D], i: int, j: int) -> bool:
    '''
    判断p[i]p[j]组成的边是否为左边（其余点都在左边）
    '''
    pts_size = len(points)
    if i < 0 or i >= pts_size or j < 0 or j >= pts_size:
        return False
    for k in range(0, pts_size):
        if k != i and k != j and not geo.toLeft(points[i], points[j], points[k]):
            return False
    return True


def markEE(points: List[geo.Point2D]) -> List[geo.Point2D]:
    '''
    判断一条边是 extreme edge
    从一群点中找left_edge
    逆时针排序生成
    Extreme Edge Algo. O(n^3)
    '''
    pts_size = len(points)
    if pts_size <= 2:
        return []
    res = []
    marked = [False for i in range(0, pts_size)]
    convex_vertex_idx = 0
    for i in range(0, pts_size):  # O(n)
        for j in range(0, pts_size):  # O(n)
            if i != j and checkToLeftEdge(points, i, j):  # O(n)
                marked[i] = True
                res.append(points[i])
                convex_vertex_idx = j
                break
        else:
            continue
        break
    while True:  # O(n)
        found = False
        for i in range(0, pts_size):  # O(n)
            # O(n)
            if not marked[i] and i != convex_vertex_idx and checkToLeftEdge(points, convex_vertex_idx, i):
                marked[convex_vertex_idx] = True
                res.append(points[convex_vertex_idx])
                convex_vertex_idx = i
                found = True
                break
        if not found:
            break
    res.append(points[convex_vertex_idx])
    return res

# =============================================================================
# Incremental Construction Algo. O(n2)
# =============================================================================


def nextStepPt(points: List[geo.Point2D], i: int, step: int) -> geo.Point2D:
    '''
    找i点接下来step步长的点，step可正可负
    '''
    pts_size = len(points)
    if pts_size == 0:
        return geo.Point2D()
    return points[(i + step) % pts_size]


def vertexPattern(points: List[geo.Point2D], i: int, s: geo.Point2D) -> Tuple[bool, bool]:
    '''
    找出s->point[i]的pattern，即判断i的prev和next相对s->i的左右
    '''
    prev_pt = nextStepPt(points, i, -1)
    next_pt = nextStepPt(points, i, 1)
    cur_pt = points[i]
    prev_pt_left = geo.toLeft(s, cur_pt, prev_pt)
    next_pt_left = geo.toLeft(s, cur_pt, next_pt)
    return (prev_pt_left, next_pt_left)


def incremenalConstruction(points: List[geo.Point2D]) -> List[geo.Point2D]:
    pts_size = len(points)
    if pts_size <= 2:
        return points
    res = [points[0], points[1]]
    # 找到一个逆时针排列
    for i in range(2, pts_size):
        if geo.counterclockwise(points[0], points[1], points[i]):
            res.append(points[i])
            break
    for i in range(0, pts_size):  # O(n)
        t_idx = -1  # 所有的点都在右边
        s_idx = -1  # 所有的点都在左边
        for j in range(0, len(res)):  # O(n)
            if points[i] == res[j]:  # 重复点不看
                break
            prev_left, next_left = vertexPattern(res, j, points[i])
            if not prev_left and not next_left:
                t_idx = j
            if prev_left and next_left:
                s_idx = j
        if t_idx < 0 or s_idx < 0:
            continue
        if s_idx > t_idx:
            new_res = copy.deepcopy(res[:t_idx+1])
            new_res.append(points[i])
            new_res.extend(res[s_idx:])
            res = new_res
        else:
            new_res = copy.deepcopy(res[s_idx: t_idx+1])
            new_res.append(points[i])
            res = new_res
    return res

# =============================================================================
# Jarvis March O(nh)
# =============================================================================


def LTL(points: List[geo.Point2D]) -> int:
    '''
    寻找the lowest-then-leftmost point
    Returns
    -------
    int
        LTL idx.
    '''
    ltl_idx = 0
    for i in range(1, len(points)):
        if points[i].y_ < points[ltl_idx].y_ or (points[i].y_ == points[ltl_idx].y_ and points[i].x_ < points[ltl_idx].x_):
            ltl_idx = i
    return ltl_idx


def Jarvis1(points: List[geo.Point2D]) -> List[geo.Point2D]:
    '''
    Jarvis算法计算convex point
    '''
    marked = [False for i in range(0, len(points))]
    res = []
    ltl_idx = LTL(points)
    res.append(points[ltl_idx])
    marked[ltl_idx] = True
    vector_origin = geo.Vector2D(1.0, 0.0)
    while True:
        angle_min = sys.float_info.max
        found = False
        next_idx = -1
        for i in range(0, len(points)):
            if i == ltl_idx:
                continue
            angle_diff = geo.calcAngleDiff(vector_origin, geo.Vector2D(
                points[i].x_ - points[ltl_idx].x_, points[i].y_ - points[ltl_idx].y_))
            if angle_diff >= 0:
                continue
            if math.fabs(angle_diff) < math.fabs(angle_min):
                angle_min = angle_diff
                next_idx = i
                found = True
        if not found or marked[next_idx]:
            break
        vector_origin = geo.Vector2D(
            points[next_idx].x_ - points[ltl_idx].x_, points[next_idx].y_ - points[ltl_idx].y_)
        ltl_idx = next_idx
        marked[next_idx] = True
        res.append(points[next_idx])
    return res
