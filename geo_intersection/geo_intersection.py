from cmath import isclose
import geometry_util as geo
from typing import List
import math


def IID(intervals: List[geo.Interval]) -> bool:
    """Interval Intersection Detection
    检测一个区间序列是否存在交叉
    """
    interval_bound_list = []
    for i in intervals:
        interval_bound_list.append(tuple(i.lower_, 'l'))
        interval_bound_list.append(tuple(i.upper_, 'u'))
    sorted(interval_bound_list, key=lambda x: x[0])
    for i in range(len(interval_bound_list) - 1):
        if interval_bound_list[i][1] == interval_bound_list[i + 1][1]:
            return True
    return False


###################################################################
## segmens intersection
###################################################################
def compare_by_x(p1: geo.Point2D, p2: geo.Point2D) -> int:
    """compares x-values of two pts
       used for ordering in T
    """
    if math.isclose(p1.x_, p2.x):
        return 0
    elif p1.x_ < p2.x_:
        return -1
    else:
        return 1


def compare_by_y(p1: geo.Point2D, p2: geo.Point2D) -> int:
    """higher y value is "less"; if y value equal, lower x value is "less"
       used for ordering in Q
    """
    if math.isclose(p1.y_, p2.y_):
        return compare_by_x(p1, p2)
    elif p1.y_ > p2.y_:
        return -1
    else:
        return 1


class Node:
    def __init__(self, value: geo.Segment2D, left, right, parent) -> None:
        self.value_ = value
        self.left_ = left
        self.right_ = right
        self.parent_ = parent
        self.slope_ = None
        if value is not None:
            self.slope_ = value.slope()

    def compare_to_key(self, p: geo.Point2D) -> int:
        """compares line segment at y-val of p to p
        """
        return compare_by_x(p, self.value_.get_x_at(p))
    
    