#include <cstdio>
#include <cstring>
#include <climits>
#include <vector>
#include <deque>
#include <queue>
#include <algorithm>

using namespace std;

typedef long long Number;

#define INFTY 150000000000
#define NMAX 10000000

struct Edge {
    int from;
    int to;
    Number weight;
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX];
static Number dist[NMAX];

/////////////////
// IndexedHeap //
/////////////////

typedef int KeyType;
typedef Number ValueType;
#define SIZEMAX NMAX

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) + 1)

static KeyType heap[SIZEMAX + 10];
static unsigned heapSize;

// O(1)
inline void make_heap() { heapSize = 0; }

// O(1)
inline unsigned heap_size() { return heapSize; }

// O(logn)
inline void swim(unsigned x) {
    while (x > 0 and dist[heap[x]] < dist[heap[PARENT(x)]]) {
        swap(heap[x], heap[PARENT(x)]);

        x = PARENT(x);
    }  // while
}

// O(logn)
inline void sink(unsigned x) {
    while (x <= heapSize) {
        // 冒泡选取最小值
        unsigned next = x;

        if (LEFT(x) <= heapSize and dist[heap[next]] > dist[heap[LEFT(x)]]) {
            next = LEFT(x);
        }

        if (RIGHT(x) <= heapSize and dist[heap[next]] > dist[heap[RIGHT(x)]]) {
            next = RIGHT(x);
        }

        // 如果x就是最小，则堆的性质已维护完毕
        if (next == x) {
            break;
        } else {
            swap(heap[x], heap[next]);
        }

        x = next;
    }  // while
}

inline KeyType top() { return heap[1]; }

inline void push(KeyType key) {
    heapSize++;
    heap[heapSize] = key;

    swim(heapSize);
}

inline void pop() {
    heap[1] = heap[heapSize];
    heapSize--;

    sink(1);
}

inline bool empty() { return heapSize == 0; }

/////////////////////
// IndexedHeap end //
/////////////////////

template <typename T>
inline T abs(const T &a) {
    return a > 0 ? a : -a;
}

void dijkstra() {
    push(1);

    while (!empty()) {
        int u = top();
        pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->to;

            if (dist[v] > dist[u] + e->weight) {
                dist[v] = dist[u] + e->weight;

                push(v);
            }
        }  // for
    }      // while
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        Number w;
        scanf("%d%d%lld", &u, &v, &w);

        G[u].push_back(new Edge({u, v, w}));
    }  // for

    for (int i = 1; i <= n; i++) {
        dist[i] = INFTY;
    }  // for
    dist[1] = 0;

    dijkstra();

    for (int i = 1; i <= n; i++) {
        if (dist[i] >= INFTY) {
            printf("-1\n");
        } else {
            printf("%lld\n", dist[i]);
        }
    }  // for

    return 0;
}  // function main
