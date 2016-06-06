#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

// #define QMAX 200000
#define QMAX 30
#define POINTS_MAX (QMAX * 4)

typedef long long ntype;

struct Point {
    int x, y;

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y <= p.y);
    }
};  // struct Point

struct Space {
    int x1, x2, y1, y2;

    void set(int _x1, int _x2, int _y1, int _y2) {
        x1 = _x1;
        x2 = _x2;
        y1 = _y1;
        y2 = _y2;
    }

    bool in(const Space &sp) const {
        return sp.x1 <= x1 && x2 <= sp.x2 && sp.y1 <= y1 && y2 <= sp.y2;
    }

    bool out(const Space &sp) const {
        return x2 < sp.x1 || x1 > sp.x2 || y2 < sp.y1 || y1 > sp.y2;
    }

    bool contain(const Point &p) const {
        return x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2;
    }
};  // struct Space

struct Node {
    struct Sum {
        Sum() {}

        ntype xyw, yw, xw, w;
    };  // struct Sum

    Node() : NE(NULL), NW(NULL), SW(NULL), SE(NULL) {}

    Space space;
    Point *point;
    Sum sum;

    Node *NE, *NW, *SW, *SE;
};  // struct Node

static Point points[POINTS_MAX + 10];
static Point *aux[POINTS_MAX + 10];
static Point *q1[POINTS_MAX + 10], *q2[POINTS_MAX + 10], *q3[POINTS_MAX + 10],
    *q4[POINTS_MAX + 10];

static Node *build(int left, int right) {
    if (right < left)
        return NULL;

    Node *x = new Node;

    if (left == right) {
        x->point = aux[left];
        x->space.set(x->point->x, x->point->x, x->point->y, x->point->y);

        return x;
    }

    int current = (left + right) / 2;
    int midx = aux[current]->x, midy = aux[current]->y;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;
    for (int i = left; i <= right; i++) {
        Point *p = aux[i];
        minx = min(minx, p->x);
        maxx = max(maxx, p->x);
        miny = min(miny, p->y);
        maxy = max(maxy, p->y);

        if (i == current)
            continue;

        if (p->x >= midx && p->y >= midy)
            q1[++c1] = p;
        else if (p->x <= midx && p->y >= midy)
            q2[++c2] = p;
        else if (p->x <= midx && p->y <= midy)
            q3[++c3] = p;
        else
            q4[++c4] = p;
    }  // for

    x->space.set(minx, maxx, miny, maxy);
    x->point = aux[current];

    int pos = left;
    for (int i = 1; i <= c1; i++)
        aux[pos++] = q1[i];
    for (int i = 1; i <= c2; i++)
        aux[pos++] = q2[i];
    for (int i = 1; i <= c3; i++)
        aux[pos++] = q3[i];
    for (int i = 1; i <= c4; i++)
        aux[pos++] = q4[i];

    x->NE = build(left, left + c1 - 1);
    x->NW = build(left + c1, left + c1 + c2 - 1);
    x->SW = build(left + c1 + c2, left + c1 + c2 + c3 - 1);
    x->SE = build(left + c1 + c2 + c3, left + c1 + c2 + c3 + c4 - 1);

    return x;
}
