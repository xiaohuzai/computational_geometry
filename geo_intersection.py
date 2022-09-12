import geometry_convex as geo
from typing import List


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