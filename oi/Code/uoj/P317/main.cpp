/**
 * TODO:
 *     1. 2-SAT: scc & construct
 *     2. Randomized test (about 200 times)
 */
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 300000

#define A 'a'
#define B 'b'
#define C 'c'
#define X 'x'
#define T 0
#define F 1

struct Graph {
    vector<int> G[NMAX + 10];

    void link(int u, int v) {
        G[u].push_back(v);
    }

    void bilink(int u, int v) {
        link(u, v);
        link(v, u);
    }

    vector<int> &operator[](int x) {
        return G[x];
    }
};

static int n, m, d;
static char S[NMAX + 10];
static Graph N, G;

inline int p(int x, int c, int t) {
    return (x - 1) * 6 + (c - A + 1) + t * 3;
}

void initialize() {
    scanf("%d%d%s%d", &n, &d, S, &m);

    for (int i = 1; i <= n; i++) {
        if (S[i] == X)
            continue;

        N.link(p(i, S[i], F), p(i, S[i], T));
        switch (S[i]) {
            case A: {
                N.bilink(p(i, B, T), p(i, C, F));
                N.bilink(p(i, C, T), p(i, B, F));
            } break;

            case B: {
                N.bilink(p(i, A, T), p(i, C, F));
                N.bilink(p(i, C, T), p(i, A, F));
            } break;

            case C: {
                N.bilink(p(i, A, T), p(i, B, F));
                N.bilink(p(i, B, T), p(i, A, F));
            } break;
        }
    }
}
