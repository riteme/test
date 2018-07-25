#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

#define NMAX 200000
#define MOD 10007

// #define FMT "%lld"
// typedef long long ntype;

#define FMT "%d"
typedef int ntype;

static ntype n;
static ntype result = 0;
static ntype m = 0;
static ntype W[NMAX + 10];
static vector<ntype> G[NMAX + 10];
static ntype DT[NMAX + 10];
static bool marked[NMAX + 10];

inline ntype read_int() {
    ntype v = 0;
    char c = getchar();
    while (c < '0' or c > '9') c = getchar();
    while ('0' <= c and c <= '9') {
        v = v * 10 + c - '0';
        c = getchar();
    }
    return v;
}

inline void read_edge() {
    ntype u, v;
    // scanf(FMT FMT, &u, &v);
    u = read_int();
    v = read_int();

    G[u].push_back(v);
    G[v].push_back(u);
}

inline void read_weight(unsigned i) {
    // scanf(FMT, &W[i]);
    W[i] = read_int();
}

ntype get_beginning();
void compute(ntype s);

int main() {
    scanf(FMT, &n);

    for (ntype i = 0; i < n - 1; i++) read_edge();
    for (ntype i = 1; i <= n; i++) read_weight(i);

    ntype s = get_beginning();
    compute(s);

    printf(FMT " " FMT, m, result);

    return 0;
}  // function main

void compute_union(ntype x);
void process(ntype x, ntype depth);
void dfs(ntype x, ntype depth);

void compute_union(ntype x) {
    for (int i = 0; i < G[x].size(); i++) {
        if (!marked[G[x][i]]) {
            for (int j = i + 1; j < G[x].size(); j++) {
                if (!marked[G[x][j]]) {
                    ntype wunion = W[G[x][i]] * W[G[x][j]];
                    result += wunion;
                    result %= MOD;

                    // printf("func compute_union(): %d * %d -> %d * %d = %d\n",
                    // G[x][i], G[x][j], W[G[x][i]], W[G[x][j]], wunion);

                    if (m < wunion) m = wunion;
                }  // if
            }      // for
        }          // if
    }              // for
}

ntype get_beginning() {
    memset(marked, false, sizeof(marked));

    ntype x = 1;
    ntype next = 0;
    while (true) {
        if (G[x].size() == 1) return x;

        for (auto i : G[x]) {
            if (!marked[i]) {
                marked[i] = true;
                next = i;
                break;
            }
        }  // for

        if (next == 0) return x;

        x = next;
        next = 0;
    }  // while
}

void dfs(ntype x, ntype depth) {
    process(x, depth);

    DT[depth] = x;
    marked[x] = true;
    for (auto u : G[x]) {
        if (!marked[u]) {
            // marked[u] = true;

            dfs(u, depth + 1);

            // marked[u] = false;
        }
    }  // foreach in G[x]
}

void process(ntype x, ntype depth) {
    if (G[x].size() > 2) compute_union(x);

    if (depth > 2) {
        ntype wunion = W[DT[depth - 2]] * W[x];
        result += wunion;
        result %= MOD;

        // printf("func dfs(): %d * %d -> %d * %d = %d\n", DT[depth - 2], x,
        // W[DT[depth - 2]], W[x], wunion);

        if (m < wunion) m = wunion;
    }
}

void compute(ntype s) {
    memset(marked, false, sizeof(marked));

    // printf("s: %d\n", s);

    dfs(s, 1);

    result = (result * 2) % MOD;
}
