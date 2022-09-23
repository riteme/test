#include <cstdio>
#include <cassert>
#include <cstdint>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

using i64 = long long;

constexpr int NMAX = 5000;
constexpr int MEMSIZE = 2000000;
constexpr i64 INF = 0xffffffffffffff;

int n, K, m, g;
i64 w[NMAX + 10];
bool mark[NMAX + 10];
bool dead[NMAX + 10];
unordered_set<int> G0[NMAX + 10], G1[NMAX + 10];
unordered_set<int> R0[NMAX + 10], R1[NMAX + 10];

struct closure_t {
    int boss;
    int size;
    int input, output;
    vector<closure_t *> children;
    closure_t *parent;
};

void _dump(vector<int> &vs, closure_t *C) {
    if (C == NULL)
        return;
    if (C->size == 1)
        vs.push_back(C->boss);
    else {
        for (auto v : C->children) {
            _dump(vs, v);
        }
    }
}

auto dump(closure_t *C) -> vector<int> {
    vector<int> vs;
    vs.reserve(C->size);
    _dump(vs, C);
    return vs;
}

int memsize;
closure_t mem[MEMSIZE];
closure_t *C[NMAX + 10];

void reset_closure(closure_t *C) {
    C->boss = 0;
    C->input = 0;
    C->output = 0;
    C->size = 0;
    C->children.clear();
    C->parent = 0;
}

auto new_closure() -> closure_t * {
    assert(memsize < MEMSIZE);
    auto p = mem + memsize;
    memsize++;
    reset_closure(p);
    return p;
}

closure_t *last = NULL;

void reset() {
    last = NULL;
    memset(w, 0, sizeof(w));
    memset(mark, 0, sizeof(mark));
    memset(dead, 0, sizeof(dead));

    for (auto &v : G0) {
        v.clear();
    }
    for (auto &v : R0) {
        v.clear();
    }
    for (auto &v : G1) {
        v.clear();
    }
    for (auto &v : R1) {
        v.clear();
    }

    memsize = 0;
    memset(C, 0, sizeof(C));
}

void link(int u, int v) {
    G0[u].insert(v);
    R0[v].insert(u);
}

int in[NMAX + 10];
bool inside[NMAX + 10], used[NMAX + 10];
i64 minw[NMAX + 10], maxw[NMAX + 10];

bool is_input(int u) {
    for (int v : R0[u]) {
        if (v <= n && !inside[v])
            return true;
    }
    return false;
}

bool is_output(int u) {
    for (int v : G0[u]) {
        if (v <= n && !inside[v])
            return true;
    }
    return false;
}

bool check_balance(closure_t *X) {
    auto us = dump(X);
    for (int u : us) {
        inside[u] = true;
        minw[u] = +INF;
        maxw[u] = -INF;
    }

    for (int u : us) {
        for (int v : G0[u]) {
            if (inside[v])
                in[v]++;
        }

        if (is_input(u)) {
            minw[u] = maxw[u] = 0;
        }
    }

    queue<int> q;
    for (int u : us) {
        if (in[u] == 0 && !used[u]) {
            used[u] = true;
            q.push(u);
        }
    }

    while (q.size()) {
        int u = q.front();
        q.pop();

        assert(minw[u] < +INF);
        assert(maxw[u] > -INF);
        minw[u] += w[u];
        maxw[u] += w[u];

        for (int v : G0[u])
        if (inside[v]) {
            minw[v] = min(minw[v], minw[u]);
            maxw[v] = max(maxw[v], maxw[u]);
            in[v]--;

            if (in[v] == 0 && !used[v]) {
                used[v] = true;
                q.push(v);
            }
        }
    }

    i64 maxc = -INF, minc = +INF;
    for (int u : us) {
        if (is_output(u)) {
            maxc = max(maxc, maxw[u]);
            minc = min(minc, minw[u]);
        }

        in[u] = 0;
        inside[u] = false;
        used[u] = false;
    }

    assert(maxc > -INF);
    assert(minc < +INF);
    return 10 * minc >= 9 * maxc;
}

auto meld(int u, int v) -> closure_t * {
    assert(C[u]->parent == NULL);
    assert(C[v]->parent == NULL);

    if (last == NULL)
        last = new_closure();
    auto X = last;

    X->size = C[u]->size + C[v]->size;
    X->input = C[u]->input;
    X->output = C[v]->output;
    X->children.push_back(C[u]);
    X->children.push_back(C[v]);

    // TODO: randomized?
    if (!mark[v] && R1[u].size() == 1 && R1[v].size() == 1) {
        // assert(C[u]->input != 0);
        X->boss = u;
        if (G1[u].size() > 1)
            X->output = 0;

        last = NULL;
        return X;
    } else if (!mark[u] && G1[v].size() == 1 && G1[u].size() == 1) {
        // assert(C[v]->output != 0);
        X->boss = v;
        if (R1[v].size() > 1)
            X->input = 0;

        last = NULL;
        return X;
    }

    return NULL;
}

void contract(int u, int v) {
    for (int y : G1[v]) {
        if (y != u) {
            G1[u].insert(y);
            R1[y].erase(v);
            R1[y].insert(u);
        }
    }
    for (int y : R1[v]) {
        if (y != u) {
            R1[u].insert(y);
            G1[y].erase(v);
            G1[y].insert(u);
        }
    }

    if (G1[u].count(v))
        G1[u].erase(v);
    if (R1[u].count(v))
        R1[u].erase(v);

    G1[v].clear();
    R1[v].clear();
    dead[v] = true;
}

struct edge_t {
    int u, v;
};

bool try_meld(int u, int v) {
    auto X = meld(u, v);
    if (X == NULL || !check_balance(X))
        return false;

    C[u]->parent = X;
    C[v]->parent = X;
    if (X->boss == u) {
        contract(u, v);
        C[u] = X;
    } else {
        contract(v, u);
        C[v] = X;
    }

    return true;
}

bool pattern1() {
    for (int u = 1; u <= n; u++)
    if (!dead[u] && C[u]->input == u) {
        int p = -1;
        bool ok = true;
        for (int v : G1[u]) {
            if (mark[v] || v == 0) {
                ok = false;
                break;
            }
            if (G1[v].size() == 1) {
                int y = *G1[v].begin();
                if (p == -1)
                    p = y;
                else if (p != y) {
                    ok = false;
                    break;
                }
            } else {
                ok = false;
                break;
            }
        }

        if (p != -1 && mark[p])
            ok = false;
        if (!ok || p == -1 || p == 0)
            continue;

        auto X = new_closure();
        X->boss = u;
        X->input = u;
        X->output = p;
        X->size = C[u]->size + C[p]->size;
        X->children.push_back(C[u]);
        X->children.push_back(C[p]);
        for (int v : G1[u]) {
            X->size += C[v]->size;
            X->children.push_back(C[v]);
        }

        vector<int> vs;
        for (int v : G1[u]) {
            vs.push_back(v);
        }
        for (int v : vs) {
            contract(u, v);
        }
        contract(u, p);

        C[u] = X;

        return true;
    };

    return false;
}

bool fuck() {
    for (int u = 1; u <= n; u++)
    if (!dead[u] /*&& !mark[u]*/) {
        for (int v : G1[u])
        if (1 <= v && v <= n && !dead[v] /*&& !mark[v]*/) {
            if (try_meld(u, v))
                return true;
        }
    };

    return false;
}

void fuck_main() {
    pattern1();
    for (int i = 0; i < 2000; i++) {
        if (!fuck())
            break;
    }
}

void print_result() {
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!dead[u] && !mark[u])
            cnt++;
    }

    printf("%d ", cnt);
    for (int u = 1; u <= n; u++) {
        if (!dead[u] && !mark[u])
            printf("%d ", u);
    }
    puts("");

    cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!dead[u])
            cnt++;
    }

    printf("%d\n", cnt);
    for (int u = 1; u <= n; u++)
    if (!dead[u]) {
        auto vs = dump(C[u]);
        printf("%zu ", vs.size());
        for (int v : vs) {
            printf("%d ", v);
        }
        puts("");
    }
}

void initialize() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", w + i);
        C[i] = new_closure();
        C[i]->size = 1;
        C[i]->boss = i;
        C[i]->input = i;
        C[i]->output = i;
    }

    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int u;
        scanf("%d", &u);
        mark[u] = true;
        // link(n + 1, u);
        // link(u, n + 1);
    }

    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        link(u, v);
    }

    link(0, 1);
    link(n, 0);

    for (int u = 0; u <= n; u++) {
        G1[u] = G0[u];
        R1[u] = R0[u];
    }
}

void naive() {
    int cnt = 0;
    for (int u = 1; u <= n; u++) {
        if (!mark[u])
            cnt++;
    }

    printf("%d ", cnt);
    for (int u = 1; u <= n; u++) {
        if (!mark[u])
            printf("%d ", u);
    }
    puts("");

    printf("%d\n", n - 1);
    printf("2 1 %d\n", n);
    for (int u = 2; u < n; u++) {
        printf("1 %d\n", u);
    }

    // ?????
}

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        initialize();
        // naive();
        fuck_main();
        print_result();
        reset();
    }

    return 0;
}