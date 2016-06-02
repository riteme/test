#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

struct Point {
    int x, y;

    bool operator<(const Point &p) {
        return x < p.x || (x == p.x && y <= p.y);
    }
};  // struct Point

struct Space {
    int x1, x2, y1, y2;

    bool in(const Space &a) const {
        return a.x1 <= x1 && x2 <= a.x2 && a.y1 <= y1 && y2 <= a.y2;
    }

    bool out(const Space &a) const {
        return x2 < a.x1 || x1 > a.x2 || y2 < a.y1 || y1 > a.y2;
    }

    bool contain(const Point &p) const {
        return x1 <= p.x && p.x <= x2 && y1 <= p.y && p.y <= y2;
    }
};  // struct Space

struct Node {
    Node() : size(0), NE(NULL), NW(NULL), SE(NULL), SW(NULL) {}

    Space space;
    Point *point;

    int size;

    Node *NE, *NW, *SE, *SW;
};  // struct Node

static int n;
static int maxheight;
static Point points[1000100];
static Point *a[1000100];
static Point *aux[1000100];
static Point *q1[1000100], *q2[1000100], *q3[1000100], *q4[1000100];

static Node *build(int left, int right, int depth) {
    if (right < left)
        return NULL;

    if (left == right) {
        maxheight = max(maxheight, depth);

        Node *x = new Node;
        Point *p = a[left];

        x->point = p;
        x->space = { p->x, p->x, p->y, p->y };
        x->size = 1;

        return x;
    }

    for (int i = left; i <= right; i++)
        aux[i] = a[i];

    int current = (left + right) / 2;
    int minx = INT_MAX, maxx = INT_MIN, miny = INT_MAX, maxy = INT_MIN;
    for (int i = left; i <= right; i++) {
        Point *p = aux[i];
        minx = min(minx, p->x);
        maxx = max(maxx, p->x);
        miny = min(miny, p->y);
        maxy = max(maxy, p->y);
    }  // for

    Node *x = new Node;
    x->point = aux[current];
    x->space = { minx, maxx, miny, maxy };
    x->size = right - left + 1;

    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    for (int i = left; i <= right; i++) {
        if (i != current) {
            Point *p = aux[i];

            if (p->x >= x->point->x && p->y >= x->point->y)
                q1[++c1] = p;
            else if (p->x <= x->point->x && p->y >= x->point->y)
                q2[++c2] = p;
            else if (p->x >= x->point->x && p->y <= x->point->y)
                q3[++c3] = p;
            else
                q4[++c4] = p;
        }
    }  // for

    int pos = left;
    for (int i = 1; i <= c1; i++, pos++)
        a[pos] = q1[i];
    for (int i = 1; i <= c2; i++, pos++)
        a[pos] = q2[i];
    for (int i = 1; i <= c3; i++, pos++)
        a[pos] = q3[i];
    for (int i = 1; i <= c4; i++, pos++)
        a[pos] = q4[i];

    x->NE = build(left, left + c1 - 1, depth + 1);
    x->NW = build(left + c1, left + c1 + c2 - 1, depth + 1);
    x->SE = build(left + c1 + c2, left + c1 + c2 + c3 - 1, depth + 1);
    x->SW = build(left + c1 + c2 + c3, left + c1 + c2 + c3 + c4 - 1, depth + 1);

    return x;
}

static int query(Node *x, const Space &sp) {
    if (!x) {
        return 0;
    }

    // printf("Querying (%d, %d)...\n", x->point->x, x->point->y);

    if (x->space.out(sp)) {
        puts("Out");
        return 0;
    } else if (x->space.in(sp)) {
        puts("In");
        return x->size;
    } else {
        return query(x->NE, sp) + query(x->NW, sp) + query(x->SE, sp) +
               query(x->SW, sp) + (sp.contain(*(x->point)) ? 1 : 0);
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);

        points[i].x = x;
        points[i].y = y;
        a[i] = points + i;
    }  // for

    sort(a + 1, a + n + 1);
    Node *tree = build(1, n, 1);
    puts("Construction completed.");
    printf("maxheight = %d\n", maxheight);

    int x1, y1, x2, y2;
    while (scanf("%d%d%d%d", &x1, &y1, &x2, &y2) != EOF) {
        printf("%d\n", query(tree, { x1, x2, y1, y2 }));
    }  // while

    return 0;
}  // function main
