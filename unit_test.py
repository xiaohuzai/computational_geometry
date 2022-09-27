# -*- coding: utf-8 -*-
"""
Created on Sun Aug 28 19:59:23 2022

@author: yan.huang
"""

import geometry_util as geo
import convex_hull as ch
import geo_intersection.geo_intersection as geo_intersection
import draw
import unittest
import numpy as np
from typing import List
import time


def genPoints(m: int) -> List[geo.Point2D]:
    x = np.random.rand(m)
    y = np.random.rand(m)
    res = []
    for i in range(0, len(x)):
        res.append(geo.Point2D(x[i], y[i]))
    return res


def genSegments(m: int) -> List[geo.Segment2D]:
    x = np.random.rand(m)
    y = np.random.rand(m)
    res = []
    for i in range(0, len(x), 2):
        res.append(
            geo.Segment2D(geo.Point2D(x[i], y[i]),
                          geo.Point2D(x[i + 1], y[i + 1])))
    return res

class TestGeomertry(unittest.TestCase):
    def test_in_triangle1(self):
        # 顺时针排序
        p = geo.Point2D(5.0, 0.0)
        q = geo.Point2D(0.0, 0.0)
        r = geo.Point2D(0.0, 5.0)
        self.assertFalse(geo.inTriangle(p, q, r, geo.Point2D(0.0, 0.0)))
        self.assertTrue(geo.inTriangle(p, q, r, geo.Point2D(1.0, 1.0)))
        self.assertFalse(geo.inTriangle(p, q, r, geo.Point2D(5.0, 5.0)))

    def test_in_triangle2(self):
        # 逆时针排序
        p = geo.Point2D(5.0, 0.0)
        q = geo.Point2D(0.0, 5.0)
        r = geo.Point2D(0.0, 0.0)
        self.assertFalse(geo.inTriangle(p, q, r, geo.Point2D(0.0, 0.0)))
        self.assertTrue(geo.inTriangle(p, q, r, geo.Point2D(1.0, 1.0)))
        self.assertFalse(geo.inTriangle(p, q, r, geo.Point2D(5.0, 5.0)))

    def test_in_convex_polygon(self):
        convex_hull = [
            geo.Point2D(0.0, 0.0),
            geo.Point2D(1.0, 0.0),
            geo.Point2D(2.0, 1.0),
            geo.Point2D(1.0, 2.0),
            geo.Point2D(0.0, 1.0)
        ]
        self.assertFalse(
            geo.inConvexPolygon(convex_hull, geo.Point2D(0.0, 0.0)))
        self.assertTrue(geo.inConvexPolygon(convex_hull, geo.Point2D(0.5,
                                                                     0.5)))

    def test_sortByAngle(self):
        pts = genPoints(10)
        draw.drawTitle("test_sortByAngle")
        draw.drawLine2Ds(pts, 'b')
        draw.drawShow()
        pts_ordered = geo.sortByAngle(geo.Point2D(0, 0), pts)
        draw.drawTitle("test_sortByAngle")
        draw.drawLine2Ds(pts_ordered, 'r')
        draw.drawShow()


class TestConvexHull(unittest.TestCase):
    def __init__(self, methodName):
        super(TestConvexHull, self).__init__(methodName)
        self.polygon_points_ = genPoints(5000)


# =============================================================================
#     def test_extremePoint(self):
#         t = time.perf_counter()
#         res = ch.extremePoint(self.polygon_points_)
#         print('test_extremePoint, time cost: {}s'.format(time.perf_counter() - t))
#         draw.drawPoint2Ds(self.polygon_points_)
#         draw.drawPoint2Ds(res)
#         draw.drawShow()
# =============================================================================

    def test_markEE(self):
        t = time.perf_counter()
        res = ch.markEE(self.polygon_points_)
        draw.drawTitle("test_markEE {}s".format(time.perf_counter() - t))
        draw.drawPoint2Ds(self.polygon_points_)
        draw.drawPoint2Ds(res, 'r')
        draw.drawLine2Ds(res)
        draw.drawShow()

    def test_incremenalConstruction(self):
        t = time.perf_counter()
        res = ch.incremenalConstruction(self.polygon_points_)
        draw.drawTitle(
            "test_incremenalConstruction {}s".format(time.perf_counter() - t))
        draw.drawPoint2Ds(self.polygon_points_)
        draw.drawLine2Ds(res)
        draw.drawShow()

    def test_Jarvis1(self):
        t = time.perf_counter()
        res = ch.Jarvis1(self.polygon_points_)
        draw.drawTitle("test_Jarvis1 {}s".format(time.perf_counter() - t))
        draw.drawPoint2Ds(self.polygon_points_)
        draw.drawLine2Ds(res)
        draw.drawShow()

    def test_Jarvis2(self):
        t = time.perf_counter()
        res = ch.Jarvis2(self.polygon_points_)
        draw.drawTitle("test_Jarvis2 {}s".format(time.perf_counter() - t))
        draw.drawPoint2Ds(self.polygon_points_)
        draw.drawLine2Ds(res)
        draw.drawShow()

    def test_GrahamScane(self):
        t = time.perf_counter()
        res = ch.GrahamScane(self.polygon_points_)
        draw.drawTitle("test_GrahamScane {}s".format(time.perf_counter() - t))
        draw.drawPoint2Ds(self.polygon_points_)
        draw.drawLine2Ds(res)
        draw.drawShow()


class TestGeoIntersection(unittest.TestCase):
    def __init__(self, methodName: str = ...) -> None:
        super().__init__(methodName)
        self.segments_ = genSegments(20)

    def test_IID(self):
        draw.drawTitle("test_draw_segments")
        draw.drawSegments(self.segments_)
        draw.drawShow()

if __name__ == '__main__':
    unittest.main()