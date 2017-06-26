import random
import sys
import numpy as np


# Line segment intersection algorithm - created by Bryce Boe
# Source - http://bryceboe.com/2006/10/23/line-segment-intersection-algorithm/
# edge AB and CD won't intersect if this returns false
def intersect(A, B, C, D):
    return ccw(A,C,D) != ccw(B,C,D) and ccw(A,B,C) != ccw(A,B,D)


def ccw(A, B, C):
    return (C.y-A.y)*(B.x-A.x) > (B.y-A.y)*(C.x-A.x)


class Coord:
    def __init__(self, x, y):
        self.x = x
        self.y = y

    def __str__(self):
        return "(%s,%s)" % (self.x, self.y)


# Choose an edge from two random vertices (and another edge from the two remaining vertices)
# Choose another set of two vertices until the two edges created don't intersect
def draw_quad(coords):
    if len(coords) != 4:
        raise AttributeError
    line_intersects = True
    while line_intersects:
        a, b = random.sample(coords, 2)
        c, d = [x for x in coords if x != a and x != b]
        line_intersects = not intersect(a, b, c, d)
    return [Coord(a, c), Coord(c, b), Coord(b, d), Coord(d, a)]


# arguments: num_iter x_min x_max y_min y_max
def main():
    print(sys.argv)
    list_of_coords = [[Coord(x, y) for x, y in zip(np.random.randint(int(sys.argv[2]), int(sys.argv[3]), 4),
                                             np.random.randint(int(sys.argv[4]), int(sys.argv[5]), 4))]
                      for _ in range(int(sys.argv[1]))]

    for coords in list_of_coords:
        print('set of vertices: %s' % ",".join(str(_) for _ in coords))
        print('resulting edges: %s' % ",".join(str(_) for _ in draw_quad(coords)))
    return

if __name__ == '__main__':
    main()
