#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

static int n, k;

struct Vector {
    Vector() {}
    Vector(double _x, double _y) : x(_x), y(_y) {}

    double x, y;
};  // struct Vector

struct Triangle {
    Vector p1, p2, p3;
};  // struct Triangle

struct Node;

struct Node {
    Triangle triangle;
    vector<Node *> child;
    int height;
};  // struct Node

#define EPSLION 0.000001

inline bool float_same(const double a, const double b) {
    return fabs(a - b) < EPSLION;
}

inline Vector subtract(const Vector &a, const Vector &b) {
    return Vector(a.x - b.x, a.y - b.y);
}

inline double cross(const Vector &a, const Vector &b) {
    return a.x * b.y - b.x * a.y;
}

inline bool contain(const Triangle &t, const Vector &p) {
    Vector p1 = subtract(p, t.p1);
    Vector p2 = subtract(p, t.p2);
    Vector p3 = subtract(p, t.p3);
    double d1 = cross(p1, p2);
    double d2 = cross(p2, p3);
    double d3 = cross(p3, p1);

    return float_same(d1, 0.0) || float_same(d2, 0.0) || float_same(d3, 0.0) ||
           (d1 > 0 && d2 > 0 && d3 > 0) || (d1 < 0 && d2 < 0 && d3 < 0);
}

inline bool contain(const Triangle &t1, const Triangle &t2) {
    return contain(t1, t2.p1) && contain(t1, t2.p2) && contain(t1, t2.p3);
}

inline double size(const Triangle &t) {
    Vector p(0.0, 0.0);
    Vector p1 = subtract(p, t.p1);
    Vector p2 = subtract(p, t.p2);
    Vector p3 = subtract(p, t.p3);
    double d1 = cross(p1, p2);
    double d2 = cross(p2, p3);
    double d3 = cross(p3, p1);

    return fabs(d1 + d2 + d3) * 0.5;
}

static Node *insert(Node *h, Triangle &t) {
    if (!h) {
        Node *p = new Node;
        p->triangle = t;

        return p;
    }

    for (unsigned i = 0; i < h->child.size(); i++) {
        if (contain(h->child[i]->triangle, t)) {
            h->child[i] = insert(h->child[i], t);
            h->child[i]->height = h->height + 1;

            return h;
        }
    }

    h->child.push_back(insert(NULL, t));
    h->child[h->child.size() - 1]->height = h->height + 1;
    return h;
}

static Triangle tri[100];

static void initailize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf%lf%lf%lf%lf", &tri[i].p1.x, &tri[i].p1.y, &tri[i].p2.x,
              &tri[i].p2.y, &tri[i].p3.x, &tri[i].p3.y);
    }  // for
}

static double dfs(Node *h) {
    if (!h)
        return 0.0;

    if (h->height < k) {
        double sum = 0.0;

        for (unsigned i = 0; i < h->child.size(); i++) {
            sum += dfs(h->child[i]);
        }

        return sum;
    } else {
        double fix = 0.0;

        for (unsigned i = 0; i < h->child.size(); i++) {
            fix += size(h->child[i]->triangle);
        }

        return size(h->triangle) - fix;
    }
}

static bool cmp(const Triangle &a, const Triangle &b) {
    return size(a) > size(b);
}

int main() {
    initailize();
    sort(tri + 1, tri + n + 1, cmp);

    Triangle ground;
    ground.p1.x = -1000.0;
    ground.p1.y = -1000.0;
    ground.p2.x = 1000.0;
    ground.p2.y = -1000.0;
    ground.p3.x = -1000.0;
    ground.p3.y = 1000.0;
    Node *tree = NULL;
    tree = insert(tree, ground);
    tree->height = 0;

    for (int i = 1; i <= n; i++) {
        tree = insert(tree, tri[i]);
    }  // for

    double all;

    if (k == 0) {
        double fix = 0.0;
        for (unsigned i = 0; i < tree->child.size(); i++) {
            fix += size(tree->child[i]->triangle);
        }

        all = 10000.0 - fix;
    } else
        all = dfs(tree);

    printf("%.5lf", all / 10000.0);

    return 0;
}  // function main
