#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000

struct Point {
    int x, y;

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y <= p.y);
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
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
    Node() : value(0), sum(0), NE(NULL), NW(NULL), SE(NULL), SW(NULL) {}

    Space space;
    Point *point;
    int value;
    int sum;

    Node *NE, *NW, *SE, *SW;
};  // struct Node

#define OP_ADD 1
#define OP_QUERY 2

struct Operation {
    int type;
    int x, y, z, w;
};  // struct Operation

static int opcnt;
static Operation op[NMAX];
static int n;
static Point points[NMAX];
static Point *a[NMAX], *aux[NMAX], *q1[NMAX], *q2[NMAX], *q3[NMAX], *q4[NMAX];
static Node *tree;

static Node *build(int left, int right) {
    if (right < left)
        return NULL;

    Node *x = new Node;

    if (left == right) {
        x->point = a[left];
        x->space.set(x->point->x, x->point->x, x->point->y, x->point->y);

        return x;
    }

    for (int i = left; i <= right; i++)
        aux[i] = a[i];

    int current = (left + right) / 2;
    int midx = aux[current]->x, midy = aux[current]->y;
    int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = left; i <= right; i++) {
        Point *p = aux[i];
        minx = min(minx, p->x);
        maxx = max(maxx, p->x);
        miny = min(miny, p->y);
        maxy = max(maxy, p->y);

        if (i != current) {
            if (p->x >= midx && p->y >= midy)
                q1[++c1] = p;
            else if (p->x <= midx && p->y >= midy)
                q2[++c2] = p;
            else if (p->x >= midx && p->y <= midy)
                q3[++c3] = p;
            else
                q4[++c4] = p;
        }
    }  // for

    x->space.set(minx, maxx, miny, maxy);
    x->point = aux[current];

    int pos = left;
    for (int i = 1; i <= c1; i++, pos++)
        a[pos] = q1[i];
    for (int i = 1; i <= c2; i++, pos++)
        a[pos] = q2[i];
    for (int i = 1; i <= c3; i++, pos++)
        a[pos] = q3[i];
    for (int i = 1; i <= c4; i++, pos++)
        a[pos] = q4[i];

    x->NE = build(left, left + c1 - 1);
    x->NW = build(left + c1, left + c1 + c2 - 1);
    x->SE = build(left + c1 + c2, left + c1 + c2 + c3 - 1);
    x->SW = build(left + c1 + c2 + c3, left + c1 + c2 + c3 + c4 - 1);

    return x;
}

static void modify(Node *x, const Point &p, int v) {
    if (!x)
        return;

    if (*x->point == p) {
        x->value += v;
        x->sum += v;
    } else {
        if (x->NE && x->NE->space.contain(p))
            modify(x->NE, p, v);
        else if (x->NW && x->NW->space.contain(p))
            modify(x->NW, p, v);
        else if (x->SE && x->SE->space.contain(p))
            modify(x->SE, p, v);
        else if (x->SW && x->SW->space.contain(p))
            modify(x->SW, p, v);

        x->sum += v;
    }
}

static int query(Node *x, const Space &sp) {
    if (!x)
        return 0;
    if (x->space.in(sp))
        return x->sum;
    if (x->space.out(sp))
        return 0;

    return query(x->NE, sp) + query(x->NW, sp) + query(x->SE, sp) +
           query(x->SW, sp) + (sp.contain(*x->point) ? x->value : 0);
}

inline Point make_point(int x, int y) {
    Point p;
    p.x = x;
    p.y = y;

    return p;
}

inline Space make_space(int x1, int y1, int x2, int y2) {
    Space sp;
    sp.set(x1, x2, y1, y2);

    return sp;
}

static void initialize() {
    int _;
    scanf("%d%d", &_, &_);

    int command;
    while (scanf("%d", &command) && command != 3) {
        if (command == 1) {
            int x, y, v;
            scanf("%d%d%d", &x, &y, &v);

            Operation &p = op[++opcnt];
            p.type = OP_ADD;
            p.x = x;
            p.y = y;
            p.z = v;

            points[++n].x = x;
            points[n].y = y;
            a[n] = &points[n];
        } else {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            Operation &p = op[++opcnt];
            p.type = OP_QUERY;
            p.x = x1;
            p.y = y1;
            p.z = x2;
            p.w = y2;
        }
    }  // while

    sort(a + 1, a + n + 1);
    int i = 2, j = 2;
    while (j <= n) {
        if (*a[j] == *a[j - 1]) {
            n--;
        } else {
            a[i] = a[j];
            i++;
        }

        j++;
    }  // while

    tree = build(1, n);
}

int main() {
    freopen("mokia.in", "r", stdin);
    freopen("mokia.out", "w", stdout);
    initialize();

    for (int i = 1; i <= opcnt; i++) {
        Operation &p = op[i];

        if (p.type == OP_ADD)
            modify(tree, make_point(p.x, p.y), p.z);
        else
            printf("%d\n", query(tree, make_space(p.x, p.y, p.z, p.w)));
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
