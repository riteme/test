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
    int id;
    Space space;
    Point *point;
    int sum;

    Node *left, *right;
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
static Point *aux[NMAX], *q1[NMAX], *q2[NMAX], *q3[NMAX], *q4[NMAX];
static Node *tree;

#define AXIS_X 1
#define AXIS_Y 2
inline int next_axis(int id) {
    return (id % 2) + 1;
}

static bool cmp_x(const Point *a, const Point *b) {
    return a->x < b->x;
}

static bool cmp_y(const Point *a, const Point *b) {
    return a->y < b->y;
}

static Node *build(int left, int right, int axis) {
    if (right < left)
        return NULL;

    int mid = (left + right) / 2;
    if (axis == AXIS_X) {
        sort(aux + left, aux + right + 1, cmp_x);
    }
}

static void modify(Node *x, const Point &p, int v) {}

static int query(Node *x, const Space &sp) {}

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

static bool cmp(const Point *a, const Point *b) {
    return *a == *b;
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
            aux[n] = &points[n];
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

    sort(aux + 1, aux + n + 1);
    n = unique(aux + 1, aux + n + 1, cmp) - aux - 1;
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
