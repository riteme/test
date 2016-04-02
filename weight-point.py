n = int(input())
points = []
for i in range(0, n):
    data = [int(x) for x in input().split(" ")]
    points.append((data[0], data[1]))

def add(a, b):
    return (a[0] + b[0], a[1] + b[1])

def subtract(a, b):
    return (a[0] - b[0], a[1] - b[1])

def lerp(a, r):
    return (a[0] * r, a[1] * r)

c = points[0]
w = 1.0
for p in points[1:]:
    d = subtract(c, p)
    c = lerp(d, w / (w + 1.0))
    c = add(c, p)
    w += 1.0

print(c)
