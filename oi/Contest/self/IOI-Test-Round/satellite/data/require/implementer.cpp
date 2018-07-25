/**
 * Input data format
 * n mode limit
 * [input tree]
 * n: Node count
 * mode: 0/1/2/3:
 *     0: randomized edge addition
 *     1: maximum 3logn randomized edge addition in 0 to logn
 *     2: maximum 3logn randomized edge addition in logn to 0
 *     3: custom tree
 * [input tree]: n - 1 pairs (u, v), representing n - 1 edges in the tree.
 */

// #define NDEBUG

#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>

#include <algorithm>

#include "satellite.h"

using namespace std;

#ifndef NDEBUG
#define DEBUGF(message, ...) fprintf(stderr, message, __VA_ARGS__);
#define DEBUG(message) fprintf(stderr, message);
#else
#define DEBUGF(message, ...)
#define DEBUG(message)
#endif  // IFNDEF NDEBUG

#define NMAX 100

namespace {

struct IOLocker {
    const int MAX_MOGIC_DUP = 100;
    IOLocker() : in(STDIN_FILENO), out(STDOUT_FILENO) {
        srand(time(0));
        lock();
    }

    void lock() {
        int cnt = rand() % MAX_MOGIC_DUP;

        for (int i = 0; i < cnt; i++) {
            dup(STDERR_FILENO);
        }  // for

        int nin = dup(in);
        fclose(stdin);
        close(in);
        in = nin;

        int nout = dup(out);
        fclose(stdout);
        close(out);
        out = nout;

        stdin = stdout = NULL;
    }

    void unlock() {
        stdin = fdopen(in, "r");
        stdout = fdopen(out, "w");
    }

    int in, out;
};  // struct IOLocker

static IOLocker io __attribute__((init_priority(101)));

static int n, m, cnt, limit, mode;
static int fa[NMAX + 10];
static bool mat[NMAX + 10][NMAX + 10];
static struct Edge { int u, v; } edges[NMAX * NMAX + 10];

inline int find(int x) {
    return fa[x] ? fa[x] = find(fa[x]) : x;
}

inline void link(int x, int y) {
    x = find(x);
    y = find(y);

    if (x != y)
        fa[x] = y;
}

template <typename... TArgs>
void score(double score, const char *message, const TArgs... args) {
    io.unlock();
    printf("%.1lf ", score);
    printf(message, args...);
    io.lock();
    exit(0);
}

bool cmp1(const Edge &a, const Edge &b) {
    return __builtin_ctz(a.u ^ a.v) > __builtin_ctz(b.u ^ b.v);
}

bool cmp2(const Edge &a, const Edge &b) {
    return __builtin_clz(a.u ^ a.v) > __builtin_clz(b.u ^ b.v);
}
}

bool query(int a[], size_t na, int b[], size_t nb) {
    if (cnt == limit)
        score(0.0, "NAÏVE!!! Query limit exceeded (limit = %d)\n", limit);

    cnt++;

    DEBUGF("query #%d:\n    a[]: {", cnt);
    for (size_t i = 0; i < na; i++) {
        DEBUGF("%d", a[i]);

        if (i + 1 < na)
            DEBUG(" ");
    }  // for

    DEBUG("}\n    b[]: {");
    for (size_t i = 0; i < nb; i++) {
        DEBUGF("%d", b[i]);

        if (i + 1 < nb)
            DEBUG(" ");
    }  // for

    DEBUG("}\n");

    for (size_t i = 0; i < na; i++) {
        for (size_t j = 0; j < nb; j++) {
            if (mat[a[i]][b[j]]) {
                DEBUGF("query: true (%d - %d)\n\n", a[i], b[j]);
                return true;
            }
        }  // for
    }      // for

    DEBUG("query: false\n\n");
    return false;
}

int main(int argc, char *argv[]) {
    // freopen("data.out", "w", stderr);

    long seed = time(0);

    if (argc > 1) {
        DEBUG("srand: specified seed used.\n");
        seed = atoll(argv[1]);
    }

    srand(seed);
    DEBUGF("srand: seed = %ld\n", seed);

    io.unlock();

    scanf("%d%d%d", &n, &mode, &limit);

    if (mode == 3) {
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            edges[++m] = { u, v };
        }  // for
    } else {
        for (int i = 1; i <= n; i++) {
            for (int j = i + 1; j <= n; j++) {
                edges[++m] = { i, j };
            }  // for
        }      // for
    }

    io.lock();

    if (mode < 3)
        random_shuffle(edges + 1, edges + m + 1);

    switch (mode) {
        case 1: {
            sort(edges + 1, edges + m + 1, cmp1);
        } break;

        case 2: {
            sort(edges + 1, edges + m + 1, cmp2);
        } break;
    }  // switch to mode

    initialize(n);
    for (int i = 1; i <= m; i++) {
        Edge e = edges[i];

        if (find(e.u) != find(e.v)) {
            link(e.u, e.v);
            mat[e.u][e.v] = mat[e.v][e.u] = true;
            DEBUGF("main: edge %d - %d added.\n", e.u, e.v);

            int x, y;
            search(x, y);

            if ((x != e.u || y != e.v) && (x != e.v || y != e.u)) {
                score(0.0, "NAÏVE!!! Expected %d - %d, but got %d - %d\n", e.u,
                      e.v, x, y);
                return 0;
            }
        }
    }  // for

    score(1.0, "EXCITED!!! Query used: %d\n", cnt);

    return 0;
}  // function main
