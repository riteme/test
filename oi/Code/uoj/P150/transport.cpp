/**
 * O(n log n)算法，自带大常数......
 * 树剖求LCA普遍比倍增快
 * 两个堆维护可删除堆可能比multiset快......
 * 读入优化上了100W再考虑使用，否则然并卵
 */

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>
#include <set>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define BUFFERSIZE 65536
static size_t _pos = BUFFERSIZE;
static char _buffer[BUFFERSIZE];

inline char _getchar() {
    if (_pos == BUFFERSIZE) {
        _pos = 0;
        fread(_buffer, 1, BUFFERSIZE, stdin);
    }

    return _buffer[_pos++];
}

inline int readint() {
    int x = 0;
    char c = _getchar();

    while (c < '0' || c > '9')
        c = _getchar();
    while ('0' <= c && c <= '9') {
        x = x * 10 + (c - '0');
        c = _getchar();
    }

    return x;
}

#define NMAX 300000
#define CMAX 1000
#define LOGN 19

struct Heap {
    void push(int x) {
        _heap.push(x);
    }

    void pop(int x) {
        _deleted.push(x);
    }

    size_t size() const {
        return _heap.size() - _deleted.size();
    }

    bool empty() const {
        return size() == 0;
    }

    int top() {
        while (!_deleted.empty() && _heap.top() == _deleted.top()) {
            _heap.pop();
            _deleted.pop();
        }

        return _heap.top();
    }

    priority_queue<int> _heap;
    priority_queue<int> _deleted;
};  // struct Heap

struct Edge {
    Edge(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}

    int u;
    int v;
    int w;

    int either(int x) const {
        return u == x ? v : u;
    }
};  // struct Edge

static int n, m;
static vector<Edge *> G[NMAX + 10];
static vector<int> children[NMAX + 10];
static int father[NMAX + 10];
static int size[NMAX + 10];
static int top[NMAX + 10];
static int depth[NMAX + 10];
static int dist[NMAX + 10];
static int dist_to[NMAX + 10];
static int p1[NMAX + 10];
static int p2[NMAX + 10];
static int lca[NMAX + 10];
static int length[NMAX + 10];
static int sorted[NMAX + 10];
static int timestamp;
static int in[NMAX + 10];
static int out[NMAX + 10];

static bool marked[NMAX + 10];

static void build(int x) {
    in[x] = ++timestamp;
    marked[x] = true;

    size[x] = 1;
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (marked[v])
            continue;

        children[x].push_back(v);
        depth[v] = depth[x] + 1;
        father[v] = x;
        dist_to[v] = e->w;
        dist[v] = dist[x] + e->w;
        build(v);
        size[x] += size[v];
    }

    out[x] = timestamp;
}

static void decompose(int x) {
    int next = 0;
    for (auto v : children[x]) {
        if (size[v] > size[next])
            next = v;
    }  // foreach in children[x]

    if (next == 0)
        return;

    top[next] = top[x];
    decompose(next);

    for (auto v : children[x]) {
        if (v != next) {
            top[v] = v;
            decompose(v);
        }
    }  // foreach in children[x]
}

inline int evaluate_lca(int u, int v) {
    while (top[u] != top[v]) {
        if (depth[top[u]] > depth[top[v]])
            u = father[top[u]];
        else
            v = father[top[v]];
    }

    if (depth[u] < depth[v])
        return u;
    else
        return v;
}

static void initialize() {
    scanf("%d%d", &n, &m);
    // n = readint();
    // m = readint();

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        // u = readint();
        // v = readint();
        // w = readint();

        Edge *e = new Edge(u, v, w);
        G[u].push_back(e);
        G[v].push_back(e);
    }  // for

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", p1 + i, p2 + i);
        // p1[i] = readint();
        // p2[i] = readint();
    }

    depth[1] = 1;
    build(1);

    top[1] = 1;
    decompose(1);

    for (int i = 1; i <= m; i++) {
        lca[i] = evaluate_lca(p1[i], p2[i]);
        length[i] = dist[p1[i]] + dist[p2[i]] - 2 * dist[lca[i]];
    }

    int _cnt = 0;
    generate(sorted + 1, sorted + m + 1, [&_cnt] { return ++_cnt; });
    sort(sorted + 1, sorted + m + 1,
         [](const int a, const int b) { return length[a] > length[b]; });
}

inline bool is_father(int x, int p) {
    return in[p] <= in[x] && in[x] <= out[p];
}

inline bool is_on_path(int x, int u, int v, int p) {
    return is_father(x, p) && (is_father(u, x) || is_father(v, x));
}

inline void intersect(int u1, int v1, int u2, int v2, int &ou, int &ov) {
    int first = 0;
    int second = 0;

    auto add = [&first, &second](int x) {
        if (depth[x] > depth[first]) {
            second = first;
            first = x;
        } else if (depth[x] > depth[second])
            second = x;
    };

    add(evaluate_lca(u1, u2));
    add(evaluate_lca(u1, v2));
    add(evaluate_lca(v1, u2));
    add(evaluate_lca(v1, v2));
    ou = first;
    ov = second;
}

static int pathlen;
static int path[NMAX + 10];
static int dist_to_next[NMAX + 10];

static bool find_path(int x, int t, int pos) {
    if (x == t) {
        path[pos] = x;
        pathlen = pos;
        return true;
    }

    marked[x] = true;
    for (auto &e : G[x]) {
        int v = e->either(x);

        if (marked[v])
            continue;

        if (find_path(v, t, pos + 1)) {
            path[pos] = x;
            dist_to_next[pos] = e->w;
            return true;
        }
    }  // foreach in G[x]

    return false;
}

int main() {
    // freopen("transport.in", "r", stdin);
    // freopen("transport.out", "w", stdout);
    initialize();

    Heap edges;
    int maxlen = length[sorted[1]];
    int answer = maxlen;
    int ip1 = p1[sorted[1]], ip2 = p2[sorted[1]];
    memset(marked, 0, sizeof(marked));
    find_path(ip1, ip2, 1);
    int lpos = 1, rpos = pathlen;

    for (int i = 1; i < pathlen; i++)
        edges.push(dist_to_next[i]);

    for (int i = 2; i <= m + 1; i++) {
        int p = sorted[i];

        if (!edges.empty())
            answer = min(answer, max(maxlen - edges.top(), length[p]));
        else
            break;

        if (i > m)
            break;

        if (is_on_path(evaluate_lca(ip1, ip2), p1[p], p2[p], lca[p]) ||
            is_on_path(lca[p], ip1, ip2, evaluate_lca(ip1, ip2))) {
            int iu, iv;
            intersect(ip1, ip2, p1[p], p2[p], iu, iv);

            while (path[lpos] != iu && path[lpos] != iv) {
                edges.pop(dist_to_next[lpos]);
                lpos++;
            }

            if (path[lpos] == iv)
                swap(iu, iv);

            while (path[rpos] != iv) {
                edges.pop(dist_to_next[rpos - 1]);
                rpos--;
            }

            ip1 = iu;
            ip2 = iv;
        } else
            break;
    }  // for

    printf("%d\n", answer);

    return 0;
}  // function main
