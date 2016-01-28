#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <chrono>

using namespace std;

#define NMAX 100000
#define INFTY 2000000000000.0

struct Edge {
    int u;
    int v;
    double w;
};  // struct Edge

static int n;
static int m;
static vector<Edge> edges;
static vector<Edge *> G[3 * (NMAX + 1) + 10];
static double dist[3 * (NMAX + 1) + 10];
static int set[NMAX + 10];
static queue<int> q;

#define SIZEMAX NMAX * 3

typedef int KeyType;
typedef double ValueType;

/////////////////
// IndexedHeap //
/////////////////

#define PARENT(x) (x >> 1)
#define LEFT(x) (x << 1)
#define RIGHT(x) ((x << 1) + 1)

struct Node {
    KeyType key;
    ValueType value;
};  // struct Node

static Node heap[SIZEMAX + 10];
static unsigned pos[SIZEMAX + 10];  // 如果键值不是整型，可以改用哈希表
static unsigned heapSize;

// O(n)
inline void make_heap(unsigned size) {
    for (unsigned i = 1; i <= size; i++) {
        pos[i] = 0;
    }  // for

    heapSize = 0;
}

// O(1)
inline unsigned heap_size() {
    return heapSize;
}

// O(logn)
/**
 * 将元素上调至合适位置
 * @param key 键索引
 */
inline void swim(KeyType key) {
    unsigned x = pos[key];

    while (x > 0 and heap[x].value < heap[PARENT(x)].value) {
        swap(pos[key], pos[heap[PARENT(x)].key]);
        swap(heap[x], heap[PARENT(x)]);

        x = PARENT(x);
    }  // while
}

// O(logn)
/**
 * 将元素下沉至合适位置
 * @param key 键索引
 */
inline void sink(KeyType key) {
    unsigned x = pos[key];

    while (x <= heapSize) {
        // 冒泡选取最小值
        unsigned next = x;

        if (LEFT(x) <= heapSize and heap[next].value > heap[LEFT(x)].value) {
            next = LEFT(x);
        }

        if (RIGHT(x) <= heapSize and heap[next].value > heap[RIGHT(x)].value) {
            next = RIGHT(x);
        }

        // 如果x就是最小，则堆的性质已维护完毕
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

inline void push(KeyType key, ValueType value) {
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

/**
 * 减低某个元素的值
 * @param key   建索引
 * @param value 新值，必须比原来的值要小
 */
inline void decrease(KeyType key, ValueType value) {
    heap[pos[key]].value = value;

    swim(key);
}

// 多数情况下只有decrease派得上用场
// increase与decrease类似
// 可以自动判断新值的大小来选择increase或decrease

inline bool contain(KeyType key) {
    return pos[key] != 0;
}

inline bool empty() {
    return heapSize == 0;
}

// IndexedHeap end

template <typename T>
inline T abs(const T &a) {
    return a > 0 ? a : -a;
}

inline double w(double a, int cnt) {
    switch (cnt) {
        case 1: return a;
        case 2: return abs(1 / (1 - a));
        case 3: return abs((a - 1) / a);
    }  // switch to cnt

    return 233.3333;
}

inline void make_set() {
    for (int i = 1; i <= n; i++) {
        set[i] = i;
    }
}

inline int find_set(int x) {
    return x == set[x] ? x : set[x] = find_set(set[x]);
}

inline void union_set(int x, int y) {
    set[find_set(x)] = find_set(y);
}

void initialize() {
    scanf("%d%d", &n, &m);

    make_set();
    edges.resize(6 * m);
    unsigned index = 0;
    for (int i = 0; i < m; i++) {
        int u, v;
        double a;
        scanf("%d%d%lf", &u, &v, &a);

        union_set(u, v);

        int u1 = u, u2 = u + n, u3 = u + n + n;
        int v1 = v, v2 = v + n, v3 = v + n + n;

        edges[index].u = u1;
        edges[index].v = v2;
        edges[index].w = a;

        edges[index + 1].u = u2;
        edges[index + 1].v = v3;
        edges[index + 1].w = w(a, 2);

        edges[index + 2].u = u3;
        edges[index + 2].v = v1;
        edges[index + 2].w = w(a, 3);

        edges[index + 3].u = v1;
        edges[index + 3].v = u2;
        edges[index + 3].w = a;

        edges[index + 4].u = v2;
        edges[index + 4].v = u3;
        edges[index + 4].w = w(a, 2);

        edges[index + 5].u = v3;
        edges[index + 5].v = u1;
        edges[index + 5].w = w(a, 3);

        G[u1].push_back(&edges[index]);
        G[u2].push_back(&edges[index + 1]);
        G[u3].push_back(&edges[index + 2]);
        G[v1].push_back(&edges[index + 3]);
        G[v2].push_back(&edges[index + 4]);
        G[v3].push_back(&edges[index + 5]);

        index += 6;
    }
}

// void spfa() {
//     q.push(1);

//     while (!q.empty()) {
//         int u = q.front();
//         q.pop();

//         for (int i = 0; i < G[u].size(); i++) {
//             Edge *e = G[u][i];
//             int v = e->v;

//             if (dist[v] > dist[u] + e->w) {
//                 dist[v] = dist[u] + e->w;
//                 q.push(v);
//             }
//         }  // for
//     }      // while
// }

void dijkstra() {
    make_heap(3 * n);
    push(1, 0.0);

    while (!empty()) {
        Node node = top();
        int u = node.key;
        pop();

        for (int i = 0; i < G[u].size(); i++) {
            Edge *e = G[u][i];
            int v = e->v;

            if (dist[v] > dist[u] + e->w) {
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
    freopen("train.in", "r", stdin);
    freopen("train.out", "w", stdout);
    initialize();

    if (find_set(1) != find_set(n)) {
        printf("-1");
        return 0;
    }

    for (int i = 1; i <= 3 * n; i++) {
        dist[i] = INFTY;
    }  // for
    dist[1] = 0.0;

    dijkstra();

    printf("%.3lf", min(dist[n], min(dist[2 * n], dist[3 * n])));

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
