#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> IntPair;

class Heap {
 public:
    Heap();
    ~Heap();

    int top() {
        sync();

        if (_current.size() > 0)
            return _current.top();
        else
            return -1;
    }

    IntPair rank2() {
        sync();
        int first = _current.top();
        _current.pop();

        sync();
        int second = _current.top();
        _current.push(first);

        return make_pair(first, second);
    }

    void push(int x) {
        _current.push(x);
    }

    void pop() {
        sync();
        _current.pop();
    }

    void pop(int x) {
        _deleted.push(x);
    }

 private:
    void sync() {
        while (_deleted.size() > 0 and _current.size() > 0 and
               _deleted.top() > _current.top()) {
            _deleted.pop();
        }  // while

        while (_deleted.size() > 0 and _current.size() > 0 and
               _deleted.top() == _current.top()) {
            _deleted.pop();
            _current.pop();
        }  // while
    }

    priority_queue<int> _current;
    priority_queue<int> _deleted;
};  // class Heap

#define NMAX 200000
#define BLACK false
#define WHITE true

static int n, m;
static int blackcnt;
static bool color[NMAX + 10];
static vector<int> G[NMAX + 10];
static Heap heap1[NMAX + 10];
static Heap heap2[NMAX + 10];
static int father[NMAX + 10];
static vector<int> children[NMAX + 10];
static int size[NMAX + 10];
static int maxsize[NMAX + 10];
static bool marked[NMAX + 10];

#define LOGN 21
static int cnt;
static int seq[NMAX * 2];
static int depth[NMAX * 2];
static int pos[NMAX + 10];
static int dist[NMAX + 10];
static int st[NMAX + 10][LOGN + 1];

static void travel(int x, int d) {
    marked[x] = true;
    seq[++cnt] = x;
    depth[cnt] = dist[x] = d;
    if (pos[x] == 0)
        pos[x] = cnt;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x].size();

        if (not marked[v]) {
            travel(v, d + 1);
            seq[cnt] = x;
            depth[cnt] = d;
        }
    }  // for

    marked[x] = false;
}

static bool cmp(const int a, const int b) {
    return depth[a] < depth[b];
}

static void initialize_st() {
    for (int i = 1; i <= cnt; i++) {
        st[i][0] = i;
    }  // for

    for (int j = 1; j <= LOGN; j++) {
        for (int i = 1; i <= cnt; i++) {
            int next = i + (1 << (j - 1));
            if (next <= cnt) {
                st[i][j] = min(st[i][j - 1], st[next][j - 1], cmp);
            }
        }  // for
    }      // for
}

static int query_min(int left, int right) {
    if (left == right) {
        return depth[left];
    } else {
        int len = right - left + 1;
        int k = 0;
        while (len >> (k + 1) > 0)
            k++;
        return min(st[left][k], st[right - (1 << k) + 1][k], cmp);
    }
}

static int lca(int u, int v) {
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    return seq[query_min(pos[u], pos[v])];
}

static int get_distance(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[lca(u, v)];
}

static void update_size(int x) {
    marked[x] = true;
    size[x] = 1;
    maxsize[x] = 0;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (not marked[v]) {
            update_size(v);
            size[x] += size[v];
            maxsize[x] = max(maxsize[x], size[v]);
        }
    }  // for

    marked[x] = false;
}

static int total;

static int _choose(int x) {
    marked[x] = true;
    int answer = x;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        maxsize[v] = max(maxsize[v], total - size[v]);
        int result = _choose(v);
        if (maxsize[result] < maxsize[answer]) {
            answer = result;
        }
    }  // for

    marked[x] = false;
    return answer;
}

static int choose(int x) {
    update_size(x);
    total = size[x];
    return _choose(x);
}

static void make_heap1(int x, int u, int d) {
    marked[u] = true;

    heap1[x].push(d);
    for (unsigned i = 0; i < G[u].size(); i++) {
        int v = G[u][i];

        if (not marked[v]) {
            make_heap1(x, v, d + 1);
        }
    }  // for

    marked[u] = false;
}

static int setup(int x) {
    x = choose(x);
    make_heap1(x, x, 0);

    marked[x] = true;
    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (not marked[v]) {
            children[x].push_back(v);
            int r = setup(v);
            father[r] = x;
        }
    }  // for

    for (unsigned i = 0; i < children[x].size(); i++) {
        int v = children[x][i];

        heap2[x].push(heap1[v].top());
    }  // for

    return x;
}

static void turn_on(int x) {
    blackcnt--;

    int ox = x;
    heap1[x].pop(0);
    while (father[x]) {
        int f = father[x];
        int d = get_distance(ox, f);

        heap1[f].pop(d);
        if (heap2[f].top() == d) {
            heap2[f].pop(d);
        }

        x = f;
    }  // while
}

static void turn_off(int x) {
    blackcnt++;

    heap1[x].push(0);
    while (father[x]) {
        int f = father[x];
        int d = get_distance(f, x);

        heap1[f].push(d);
        if (heap1[f].top() < d) {
        }

        x = f;
    }  // while
}

inline void add_edge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

static void initialize() {
    scanf("%d", &n);
    blackcnt = n;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        add_edge(u, v);
    }  // for
}

int main() {
    initialize();
    travel(1, 0);
    initialize_st();
    setup(1);

    scanf("%d", &m);
    char buffer[10];
    for (int i = 1; i <= m; i++) {
        scanf("%s", buffer);

        if (buffer[0] == 'G') {
            if (blackcnt == 0) {
                puts("-1");
            } else if (blackcnt == 1) {
                puts("0");
            } else {
                IntPair a = heap1[1].rank2();
                printf("%d\n", a.first + a.second);
            }
        } else {  // C
            int x;
            scanf("%d", &x);

            if (color[x] == BLACK) {
                turn_on(x);
            } else {
                turn_off(x);
            }
        }
    }  // for

    return 0;
}  // function main
