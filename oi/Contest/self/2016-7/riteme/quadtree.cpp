#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define QMAX 200000
// #define QMAX 30
#define POINTS_MAX (QMAX * 4)

typedef long long ntype;

struct Point {
    Point() {}
    Point(int _x, int _y) : x(_x), y(_y) {}

    int x, y;

    bool operator<(const Point &p) const {
        return x < p.x || (x == p.x && y <= p.y);
    }

    bool operator==(const Point &p) const {
        return x == p.x && y == p.y;
    }
};  // struct Point

struct Space {
    Space() {}
    Space(int _x1, int _x2, int _y1, int _y2)
            : x1(_x1), x2(_x2), y1(_y1), y2(_y2) {}

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

struct Sum {
    Sum() : xyw(0), xw(0), yw(0), w(0) {}
    Sum(ntype _xyw, ntype _xw, ntype _yw, ntype _w)
            : xyw(_xyw), xw(_xw), yw(_yw), w(_w) {}

    ntype xyw, xw, yw, w;
};  // struct Sum

struct Node {
    Node() : NE(NULL), NW(NULL), SW(NULL), SE(NULL) {}

    Space space;
    Point *point;
    ntype w;
    Sum sum;

    Node *NE, *NW, *SW, *SE;
};  // struct Node

inline ntype sum_xyw(Node *x) {
    return x ? x->sum.xyw : 0;
}

inline ntype sum_xw(Node *x) {
    return x ? x->sum.xw : 0;
}

inline ntype sum_yw(Node *x) {
    return x ? x->sum.yw : 0;
}

inline ntype sum_w(Node *x) {
    return x ? x->sum.w : 0;
}

inline void update(Node *x) {
    x->sum.w = sum_w(x->NE) + sum_w(x->NW) + sum_w(x->SW) + sum_w(x->SE) + x->w;
    x->sum.xw = sum_xw(x->NE) + sum_xw(x->NW) + sum_xw(x->SW) + sum_xw(x->SE) +
                x->point->x * x->w;
    x->sum.yw = sum_yw(x->NE) + sum_yw(x->NW) + sum_yw(x->SW) + sum_yw(x->SE) +
                x->point->y * x->w;
    x->sum.xyw = sum_xyw(x->NE) + sum_xyw(x->NW) + sum_xyw(x->SW) +
                 sum_xyw(x->SE) + x->point->x * x->point->y * x->w;
}

static int cnt;
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

static void modify(Node *x, const Point &p, ntype delta) {
    if (!x || !x->space.contain(p))
        return;

    if (*x->point == p)
        x->w += delta;
    else {
        modify(x->NE, p, delta);
        modify(x->NW, p, delta);
        modify(x->SW, p, delta);
        modify(x->SE, p, delta);
    }

    update(x);
}

static Sum query(Node *x, const Point &p) {
    if (!x || (x->space.x2 < p.x && x->space.y2 < p.y))
        return Sum(0, 0, 0, 0);
    if (p.x <= x->space.x1 && p.y <= x->space.y1)
        return x->sum;

    Sum s1 = query(x->NE, p);
    Sum s2 = query(x->NW, p);
    Sum s3 = query(x->SW, p);
    Sum s4 = query(x->SE, p);
    Sum s;
    s.xyw = s1.xyw + s2.xyw + s3.xyw + s4.xyw;
    s.xw = s1.xw + s2.xw + s3.xw + s4.xw;
    s.yw = s1.yw + s2.yw + s3.yw + s4.yw;
    s.w = s1.w + s2.w + s3.w + s4.w;

    if (p.x <= x->point->x && p.y <= x->point->y) {
        s.w += x->w;
        s.xw += x->point->x * x->w;
        s.yw += x->point->y * x->w;
        s.xyw += x->point->x * x->point->y * x->w;
    }

    return s;
}

enum CommandType { COMM_ADD = 1, COMM_QUERY = 2 };  // enum CommandType

struct Command {
    CommandType type;
    int x1, x2, y1, y2;
    ntype v;
};  // struct Command

static int q;
static Command ops[QMAX + 10];
static Node *tree;

static void initialize() {
    int _;
    scanf("%d%d", &_, &_);

    while (true) {
        int command;
        scanf("%d", &command);

        if (command == 3)
            break;

        q++;
        scanf("%d%d%d%d", &ops[q].x1, &ops[q].y1, &ops[q].x2, &ops[q].y2);
        if (command == 1) {
            scanf("%lld", &ops[q].v);
            ops[q].type = COMM_ADD;

            points[++cnt] = Point(ops[q].x1 - 1, ops[q].y1 - 1);
            points[++cnt] = Point(ops[q].x1 - 1, ops[q].y2);
            points[++cnt] = Point(ops[q].x2, ops[q].y1 - 1);
            points[++cnt] = Point(ops[q].x2, ops[q].y2);
        } else {
            ops[q].type = COMM_QUERY;
        }
    }  // while

    sort(points + 1, points + cnt + 1);
    cnt = unique(points + 1, points + cnt + 1) - points - 1;
    for (int i = 1; i <= cnt; i++) {
        aux[i] = points + i;
    }  // for

    tree = build(1, cnt);
}

inline ntype evaluate(const Point &p) {
    Sum s = query(tree, p);

    return s.xyw - (p.x - 1) * s.yw - (p.y - 1) * s.xw +
           (p.x - 1) * (p.y - 1) * s.w;
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("quadtree.out", "w", stdout);
    initialize();

    for (int i = 1; i <= q; i++) {
        Command &op = ops[i];

        if (op.type == COMM_ADD) {
            modify(tree, Point(op.x1 - 1, op.y1 - 1), op.v);
            modify(tree, Point(op.x1 - 1, op.y2), -op.v);
            modify(tree, Point(op.x2, op.y1 - 1), -op.v);
            modify(tree, Point(op.x2, op.y2), op.v);
        } else {
            ntype answer = evaluate(Point(op.x1, op.y1)) -
                           evaluate(Point(op.x2 + 1, op.y1)) -
                           evaluate(Point(op.x1, op.y2 + 1)) +
                           evaluate(Point(op.x2 + 1, op.y2 + 1));

            printf("%lld\n", answer);
        }
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
