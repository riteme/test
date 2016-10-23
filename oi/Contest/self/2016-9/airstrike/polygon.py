from functools import cmp_to_key

def construct(points):
    leftmost = None
    for p in points:
        if leftmost is None or p[0] > leftmost[0] or (p[0] == leftmost[0] and p[1] < leftmost[1]):
           leftmost = p

    def subtract(u, v):
        return (u[0] - v[0], u[1] - v[1])

    def cross(u, v):
        return u[0] * v[1] - u[1] * v[0]

    def length(u):
        return u[0]**2 + u[1]**2

    def compare(u, v):
        pu = subtract(u, leftmost)
        pv = subtract(v, leftmost)
        if pu[0] == pv[0] and pu[1] == pv[1]:
            return 0
        elif cross(pu, pv) > 0 or (cross(pu, pv) == 0 and length(pu) < length(pv)):
            return -1
        else:
            return 1

    result = [p for p in points if p != leftmost]
    result = sorted(result, key = cmp_to_key(compare))
    return [leftmost] + result
