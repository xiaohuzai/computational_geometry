# -*- coding: utf-8 -*-
"""
Created on Mon Aug 29 11:31:41 2022

@author: yan.huang
"""

from turtle import width
import geometry_convex as geo
from typing import List
import matplotlib.pyplot as plt

def drawTitle(s):
    plt.title(s)

def drawPoint2Ds(points: List[geo.Point2D], color='b'):
    x = [p.x_ for p in points]
    y = [p.y_ for p in points]
    plt.scatter(x, y, c=color)


def drawLine2Ds(points: List[geo.Point2D], color='r'):
    x = [p.x_ for p in points]
    y = [p.y_ for p in points]
    size = len(points)
    for i in range(0, size):
        plt.annotate(str(i), (x[i], y[i]))
        plt.arrow(x[i],
                  y[i],
                  x[(i + 1) % size] - x[i],
                  y[(i + 1) % size] - y[i],
                  length_includes_head=True,
                  color=color)

def drawShow():
    plt.show()
    
    
