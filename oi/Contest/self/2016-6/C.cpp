#include <cstdio>
#include <cstring>
#include <climits>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n;

struct Point {
    int x, y, z, t;
    int answer;
};  // struct Point

static Point points[NMAX + 10];
static Point *sorted[NMAX + 10];

static bool cmp(const Point *a, const Point *b) {
    return a->t < b->t;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d%d%d%d", &points[i].x, &points[i].y, &points[i].z,
              &points[i].t);
        sorted[i] = &points[i];
    }  // for

    sort(sorted + 1, sorted + n + 1, cmp);
}

struct Cube {
    int x1, x2, y1, y2, z1, z2;

    bool empty() {
        return x1 == x2 || y1 == y2 || z1 == z2;
    }

    bool out(const Cube &x) {
        return (x2 < x.x1 || x1 > x.x2) || (y2 < x.y1 || y1 > x.y2) ||
               (z2 < x.z1 || z1 > x.z2);
    }

    bool in(const Cube &x) {
        return (x.x1 <= x1 && x2 <= x.x2) && (x.y1 <= y1 && y2 <= x.y2) &&
               (x.z1 <= z1 && z2 <= x.z2);
    }
};  // struct Cube

struct Node {
    Node()
            : sum(0)
            , c1(NULL)
            , c2(NULL)
            , c3(NULL)
            , c4(NULL)
            , c5(NULL)
            , c6(NULL)
            , c7(NULL)
            , c8(NULL) {}

    Cube range;
    int sum;

    Node *c1, *c2, *c3, *c4, *c5, *c6, *c7, *c8;
};  // struct Node

inline void split(const Cube &target, Cube &c1, Cube &c2, Cube &c3, Cube &c4,
                  Cube &c5, Cube &c6, Cube &c7, Cube &c8) {
    int midx = (target.x1 + target.x2) / 2;
    int midy = (target.y1 + target.y2) / 2;
    int midz = (target.z1 + target.z2) / 2;

    c1 = { target.x1, midx, target.y1, midy, target.z1, midz };
    c2 = { midx + 1, target.x2, target.y1, midy, target.z1, midz };
    c3 = { target.x1, midx, midy + 1, target.y2, target.z1, midz };
    c4 = { midx + 1, target.x2, midy + 1, target.y2, target.z1, midz };
    c5 = { target.x1, midx, target.y1, midy, midz + 1, target.z2 };
    c6 = { midx + 1, target.x2, target.y1, midy, midz + 1, target.z2 };
    c7 = { target.x1, midx, midy + 1, target.y2, midz + 1, target.z2 };
    c8 = { midx + 1, target.x2, midy + 1, target.y2, midz + 1, target.z2 };
}

static int query(Node *x, const Cube &range) {
    if (!x) {
        return 0;
    }

    if (x->range.out(range))
        return 0;
    else if (x->range.in(range))
        return x->sum;
    else
        return query(x->c1, range) + query(x->c2, range) + query(x->c3, range) +
               query(x->c4, range) + query(x->c5, range) + query(x->c6, range) +
               query(x->c7, range) + query(x->c8, range);
}

static Node *increase(Node *x, int x1, int y1, int z1) {
    if (!x) {
        x = new Node;
        x->range = { x1, x1, y1, y1, z1, z1 };
        x->sum = 1;

        return x;
    }

    if (x->range.out(Cube(x1, x1, y1, y1, z1, z1))) {
    }

    x->sum += 1;
}

int main() {
    initialize();

    int i = 1, j = 1;
    while (i <= n) {
        while (j <= n && j + 1 <= n && sorted[j]->t == sorted[j + 1]->t) {
            j++;
        }  // while

        for (int k = i; k <= j; k++) {
            for (int x = 1; x <= j; x++) {
                if (sorted[x]->x <= sorted[k]->x &&
                    sorted[x]->y <= sorted[k]->y &&
                    sorted[x]->z <= sorted[k]->z) {
                    sorted[k]->answer++;
                }
            }  // for

            sorted[k]->answer--;
        }  // for

        i = j = j + 1;
    }  // while

    for (int pos = 1; pos <= n; pos++) {
        printf("%d\n", points[pos].answer);
    }  // for

    return 0;
}  // function main
