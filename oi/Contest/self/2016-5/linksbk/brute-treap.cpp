#include <cassert>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <bitset>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000
#define COLORMAX 200000
#define COLORINDEXMAX 1000000

static int color[NMAX + 10];
static int _cnt;
static int _hash[COLORINDEXMAX + 10];

inline int colorhash(int x) {
    if (_hash[x] == 0)
        _hash[x] = ++_cnt;

    return _hash[x];
}

typedef bitset<COLORMAX + 10> ColorMap;

static int n, m;
static vector<int> G[NMAX + 10];
static int in[NMAX + 10];
static int out[NMAX + 10];
static int colordata[NMAX + 10];
static int timestamp;

static void dfs(int x) {
    in[x] = ++timestamp;

    for (unsigned i = 0; i < G[x].size(); i++) {
        int v = G[x][i];

        if (in[v] == 0) {
            dfs(v);
        }
    }  // for

    out[x] = timestamp;
}

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        int c;
        scanf("%d", &c);

        colordata[i] = colorhash(c);
    }  // for

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d%d", &u, &v);

        G[u].push_back(v);
        G[v].push_back(u);
    }  // for

    scanf("%d", &m);

    dfs(1);
    for (int i = 1; i <= n; i++) {
        color[in[i]] = colordata[i];
    }  // for
}

static int left[NMAX + 10];
static int right[NMAX + 10];
static int parent[NMAX + 10];
static ColorMap *map[NMAX + 10];

static int build(int l, int r) {
    if (r < l) {
        return 0;
    }

    if (l == r) {
        map[l]->set(color[l]);
        return l;
    }

    int x = (l + r) / 2;
    left[x] = build(l, x - 1);
    right[x] = build(x + 1, r);
    parent[left[x]] = x;
    parent[right[x]] = x;
    map[x]->set(color[x]);
    *(map[x]) |= *(map[left[x]]);
    *(map[x]) |= *(map[right[x]]);

    return x;
}

inline void left_rotate(int x) {
    assert(x);
    assert(left[x]);

    int y = left[x];
    left[x] = right[y];
    parent[left[x]] = x;
    right[y] = x;

    if (parent[x]) {
        if (left[parent[x]] == x)
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    map[y] = map[x];
    *map[x] = *(map[left[x]]) | *(map[right[x]]);
    map[x]->set(color[x]);
}

inline void right_rotate(int x) {
    assert(x);
    assert(right[x]);

    int y = right[x];
    right[x] = left[y];
    parent[right[x]] = x;
    left[y] = x;

    if (parent[x]) {
        if (left[parent[x]] == x)
            left[parent[x]] = y;
        else
            right[parent[x]] = y;
    }

    parent[y] = parent[x];
    parent[x] = y;

    map[y] = map[x];
    *map[x] = *(map[left[x]]) | *(map[right[x]]);
    map[x]->set(color[x]);
}

static void splay_to(int x, int to) {
    parent[0] = to;
    while (parent[x] != to) {
        int p1 = parent[x];
        int p2 = parent[p1];

        if (p2 == to) {
            if (left[p1] == x) {
                left_rotate(p1);
            } else {
                right_rotate(p1);
            }
        } else {
            if (left[p1] == x) {
                if (left[p2] == p1) {
                    left_rotate(p2);
                    left_rotate(p1);
                } else {
                    left_rotate(p1);
                    right_rotate(p2);
                }
            } else {
                if (left[p2] == p1) {
                    right_rotate(p1);
                    left_rotate(p2);
                } else {
                    right_rotate(p2);
                    right_rotate(p1);
                }
            }
        }
    }  // while
}

static void modify(int x, int from, int to) {
    while (x) {
        map[x]->set(to);

        if (!map[left[x]]->test(from) && !map[right[x]]->test(from)) {
            map[x]->reset(from);
        }

        x = parent[x];
    }  // while
}

int main() {
    freopen("data.in", "r", stdin);
    freopen("data.out", "w", stdout);
    initialize();
    for (int i = 0; i <= n; i++) {
        map[i] = new ColorMap;
    }  // for
    int tree = build(1, n);

    for (int i = 0; i < m; i++) {
        int command;
        scanf("%d", &command);

        if (command == 0) {
            int u, c;
            scanf("%d%d", &u, &c);

            u = in[u];
            c = colorhash(c);
            modify(u, color[u], c);
            color[u] = c;
        } else {  // 1
            int u;
            scanf("%d", &u);

            int answer;
            int s = in[u], t = out[u];
            if (1 < s && t < n) {
                splay_to(t + 1, 0);
                splay_to(s - 1, t + 1);
                tree = t + 1;

                answer = map[right[left[tree]]]->count();
            } else if (s == 1 && t == n) {
                answer = map[tree]->count();
            } else if (s == 1) {
                splay_to(t + 1, 0);
                tree = t + 1;

                answer = map[left[tree]]->count();
            } else {  // t == n
                splay_to(s - 1, 0);
                tree = s - 1;

                answer = map[right[tree]]->count();
            }

            printf("%d\n", answer);
        }
    }  // for

    fclose(stdin);
    fclose(stdout);
    return 0;
}  // function main
