#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300

struct Edge {
    Edge() : u(0), v(0), w(0) {}
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u;
    int v;
    int w;
};  // struct Edge

typedef vector<Edge *>::iterator iterator_t;

static int n;
static int m;
static int size;
static int set[NMAX + 10];
static vector<Edge *> edges;
static int answer;

bool compare(const Edge *a, const Edge *b) {
    return a->w < b->w;
}

inline void make_set() {
    size = n;

    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }  // for
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    x = find_set(x);
    y = find_set(y);

    if (x != y) {
        set[x] = y;
        size--;
    }
}

void initialize() {
    scanf("%d %d", &n, &m);

    edges.reserve(m);
    int x, y, c;
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &x, &y, &c);

        if (x == y)
            continue;

        Edge *p = new Edge(x, y, c);
        edges.push_back(p);
    }  // for

    sort(edges.begin(), edges.end(), compare);
}

void quit() {
    printf("%d %d", n - 1, answer);
}

bool test(int limit) {
    make_set();

    for (iterator_t beg = edges.begin();
         beg != edges.end() and (*beg)->w <= limit;
         beg++) {
        Edge *e = *beg;
        union_set(e->u, e->v);
    }  // for

    return size == 1;
}

int main() {
    initialize();

    int left = 0, right = edges.size() - 1;
    while (right - left > 1) {
        int mid = (left + right) >> 1;

        bool flag = test(edges[mid]->w);
        if (flag) {
            right = mid;
        } else {
            left = mid;
        }
    }  // while

    if (left != right and !test(edges[left]->w)) {
        left = right;
    }

    answer = edges[left]->w;

    quit();
    return 0;
}  // function main
