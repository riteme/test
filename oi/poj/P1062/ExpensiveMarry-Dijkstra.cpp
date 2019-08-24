/**
 * 昂贵的聘礼
 * Dijkstra版 0ms
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 100
#define INFTY 5000000000000000LL

#define FMT "%lld"
typedef long long ntype;

struct Edge {
    Edge(ntype _from, ntype _to, ntype _w) : from(_from), to(_to), w(_w) {}

    ntype from;
    ntype to;
    ntype w;
};  // struct Edge

static ntype m;
static ntype n;
static ntype L[NMAX + 10];
static vector<Edge> edges;
static vector<Edge *> G[NMAX + 10];
static ntype dist[NMAX + 10];
static ntype maxlevel;
static ntype minlevel;
static ntype answer;

/////////////////
// IndexedHeap //
/////////////////

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) + 1)

struct Node {
    ntype key;
    ntype value;
};  // struct Node

static Node heap[NMAX + 10];
static unsigned pos[NMAX + 10];
static ntype heapSize;

// O(n)
inline void make_heap(unsigned size) {
    for (unsigned i = 1; i <= size; i++) {
        pos[i] = 0;
    }  // for

    heapSize = 0;
}

// O(1)
inline ntype heap_size() {
    return heapSize;
}

// O(logn)
inline void swim(ntype key) {
    unsigned x = pos[key];

    while (x > 0 and heap[x].value < heap[PARENT(x)].value) {
        swap(pos[key], pos[heap[PARENT(x)].key]);
        swap(heap[x], heap[PARENT(x)]);

        x = PARENT(x);
    }  // while
}

// O(logn)
inline void sink(ntype key) {
    unsigned x = pos[key];

    while (x <= heapSize) {
        unsigned next = x;

        if (LEFT(x) <= heapSize and heap[next].value > heap[LEFT(x)].value) {
            next = LEFT(x);
        }

        if (RIGHT(x) <= heapSize and heap[next].value > heap[RIGHT(x)].value) {
            next = RIGHT(x);
        }

        if (next == x) {
            break;
        } else {
            swap(pos[key], pos[heap[next].key]);
            swap(heap[x], heap[next]);
        }

        x = next;
    }  // while
}

inline Node top() {
    return heap[1];
}

inline void push(ntype key, ntype value) {
    heapSize++;
    heap[heapSize].key = key;
    heap[heapSize].value = value;
    pos[key] = heapSize;

    swim(key);
}

inline void pop() {
    pos[heap[1].key] = 0;
    heap[1] = heap[heapSize];
    pos[heap[1].key] = 1;
    heapSize--;

    sink(heap[1].key);
}

inline void decrease(unsigned key, ntype value) {
    heap[pos[key]].value = value;

    swim(key);
}

inline bool contain(ntype key) {
    return pos[key] != 0;
}

inline bool empty() {
    return heapSize == 0;
}

// IndexedHeap end

template <typename T>
inline T abs(const T &a) {
    return a < 0 ? -a : a;
}

void initialize() {
    scanf(FMT FMT, &m, &n);

    for (ntype i = 1; i <= n; i++) {
        ntype p, x;
        scanf(FMT FMT FMT, &p, L + i, &x);

        // 表示直接用金币换
        edges.push_back(Edge(0, i, p));

        while (x > 0) {
            ntype t, v;
            scanf(FMT FMT, &t, &v);

            edges.push_back(Edge(t, i, v));

            x--;
        }  // while
    }      // for

    // 构图
    for (unsigned i = 0; i < edges.size(); i++) {
        Edge &e = edges[i];

        G[e.from].push_back(&e);
    }  // for
}

void dijkstra(ntype s) {
    for (ntype i = 1; i <= n; i++) {
        dist[i] = INFTY;
    }  // for
    dist[s] = 0;

    make_heap(n + 1);
    push(0, 0);

    while (!empty()) {
        ntype u = top().key;
        pop();

        for (unsigned i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            ntype v = e->to;

            if (minlevel <= L[v] and L[v] <= maxlevel and
                dist[v] > dist[u] + e->w) {
                dist[v] = dist[u] + e->w;

                if (contain(v)) {
                    decrease(v, dist[v]);
                } else {
                    push(v, dist[v]);
                }
            }
        }  // for
    }      // while
}

int main() {
    initialize();

    // 枚举等级范围
    answer = INFTY;
    for (minlevel = L[1] - m; minlevel <= L[1]; minlevel++) {
        maxlevel = minlevel + m;

        dijkstra(0);

        if (dist[1] < answer) {
            answer = dist[1];
        }
    }  // for

    printf(FMT, answer);

    return 0;
}  // function main
