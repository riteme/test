/**
 * 注意更新时的顺序，先要将链上的信息从根开始依次删掉
 * 然后添加新的信息，顺序随意
 * 最后从x开始更新信息
 */

#define NDEBUG

#include <cassert>
#include <cstdio>
#include <cctype>
#include <cstring>
#include <climits>

#include <set>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define LOGN 17
#define BLACK true
#define WHITE false

struct Greater {
    bool operator()(const int a, const int b) const {
        return a > b;
    }
};

class Heap {
 public:
    size_t size() const {
        return _set.size();
    }

    bool empty() const {
        return _set.empty();
    }

    void push(int x) {
        _set.insert(x);
    }

    void pop(int x) {
        multiset<int>::iterator iter = _set.find(x);
        
        assert(iter != _set.end());
        _set.erase(iter);
    }

    int top() const {
        assert(!empty());

        return *_set.begin();
    }

    int second() const {
        assert(size() >= 2);

        return *(++_set.begin());
    }

 private:
    multiset<int, Greater> _set;
};

struct Edge {
    Edge (int v, int _w)
        : to(v), w(_w) {}

    int to;
    int w;
};

static int n, q;
static int whitecnt;
static bool color[NMAX + 10];
static vector<Edge *> G[NMAX + 10];
static int root;
static int depth[NMAX + 10];
static int father[NMAX + 10];
static int id[NMAX + 10][LOGN + 1];
static int dist[NMAX + 10][LOGN + 1];
static map<int, Heap> maxdist[NMAX + 10];
static Heap maxlen[NMAX + 10];
static Heap length[NMAX + 10];
static bool marked[NMAX + 10];
static int size[NMAX + 10];

static void evaluate_size(int x, int father = 0) {
    size[x] = 1;

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (marked[v] || v == father)
            continue;

        evaluate_size(v, x);
        size[x] += size[v];
    }
}

static int select_center(int x, int maxsize, int father = 0) {
    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (marked[v] || v == father)
            continue;

        if (size[v] > maxsize)
            return select_center(v, maxsize, x);
    }

    return x;
}

static void evaluate_dist(int x, int c, int d, int father = 0) {
    int dep = depth[c];
    id[x][dep] = d;

    if (!maxdist[c].count(d))
        maxdist[c][d] = Heap();
    maxdist[c][d].push(dist[x][dep]);

    for (size_t i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->to;

        if (marked[v] || v == father)
            continue;

        dist[v][dep] = dist[x][dep] + e->w;

        if (x == c)
            evaluate_dist(v, c, v, x);
        else
            evaluate_dist(v, c, d, x);
    }
}

inline int maxpath(int x) {
    if (length[x].size() >= 2)
        return length[x].top() + length[x].second();
    return 0;
}

inline int ans(int x) {
    assert(!maxlen[x].empty());

    return maxlen[x].top();
}

static int build(int x, int dep = 0, int top = 0) {
    evaluate_size(x);

    int p = select_center(x, size[x] >> 1);
    depth[p] = dep;
    father[p] = top;

    evaluate_dist(p, p, p);

    for (map<int, Heap>::iterator beg = maxdist[p].begin();
         beg != maxdist[p].end();
         beg++) {
        length[p].push(beg->second.top());
    }

    maxlen[p].push(maxpath(p));

    marked[p] = true;
    for (size_t i = 0; i < G[p].size(); i++) {
        Edge *e = G[p][i];
        int v = e->to;

        if (marked[v])
            continue;

        maxlen[p].push(build(v, dep + 1, p));
    }

    return ans(p);
}

static void pop_fathers(int x, int p) {
    if (p) {
        pop_fathers(x, father[p]);

        int dep = depth[p];
        Heap &heap = maxdist[p][id[x][dep]];

        if (father[p])
            maxlen[father[p]].pop(ans(p));
        maxlen[p].pop(maxpath(p));
        if (!heap.empty())
            length[p].pop(heap.top());
    }
}

static void push_fathers(int x, int p) {
    if (p) {
        int dep = depth[p];
        Heap &heap = maxdist[p][id[x][dep]];

        if (!heap.empty())
            length[p].push(heap.top());
        maxlen[p].push(maxpath(p));
        if (father[p])
            maxlen[father[p]].push(ans(p));

        push_fathers(x, father[p]);
    }
}

static void add(int x) {
    whitecnt++;
    int p = x;

    pop_fathers(x, x);
    while (p) {
        int dep = depth[p];
        Heap &heap = maxdist[p][id[x][dep]];
        heap.push(dist[x][dep]);

        p = father[p];
    }

    push_fathers(x, x);
}

static void del(int x) {
    whitecnt--;
    int p = x;
    
    pop_fathers(x, x);
    while (p) {
        int dep = depth[p];
        Heap &heap = maxdist[p][id[x][dep]];
        heap.pop(dist[x][dep]);

        p = father[p];
    }

    push_fathers(x, x);
}

static void initialize() {
    scanf("%d", &n);
    whitecnt = n;

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        G[u].push_back(new Edge(v, w));
        G[v].push_back(new Edge(u, w));
    }

    build(1);

    for (int i = 1; i <= n; i++) {
        if (depth[i] == 0) {
            root = i;
            break;
        }
    }

    scanf("%d", &q);
}

inline char get_command() {
    char c = getchar();

    while (!isalpha(c)) {
        c = getchar();
    }

    return c;
}

int main() {
    initialize();

    while (q--) {
        char command = get_command();

        if (command == 'A') {
            if (whitecnt)
                printf("%d\n", max(0, ans(root)));
            else
                puts("They have disappeared.");
        } else {
            int x;
            scanf("%d", &x);

            if (color[x] == BLACK)
                add(x);
            else
                del(x);

            color[x] ^= true;
        }
    }

    return 0;
}
