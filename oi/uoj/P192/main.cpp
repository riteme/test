#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <queue>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, w;

    int either(int x) {
        return u == x ? v : u;
    }
};  // struct Edge

#define WMAX 10000000
#define NMAX 100000

static int edge_cnt = 1;
static Edge edges[NMAX + 10];

static int n;
static vector<Edge *> G[NMAX + 10];

inline void add_edge(int u, int v, int w) {
    Edge *e = &edges[edge_cnt++];

    e->u = u;
    e->v = v;
    e->w = w;

    G[u].push_back(e);
    G[v].push_back(e);
}

static bool is_not_prime[WMAX + 10];
static int prime_cnt = 0;
static int prime[WMAX];

static void compute_primes() {
    memset(is_not_prime, false, sizeof(is_not_prime));
    is_not_prime[0] = is_not_prime[1] = true;

    for (int i = 2; i <= WMAX; i++) {
        if (!is_not_prime[i]) {
            prime[prime_cnt++] = i;
        }

        for (int j = 0; j < prime_cnt && i * prime[j] <= WMAX; j++) {
            is_not_prime[i * prime[j]] = true;

            if (i % prime[j] == 0) {
                break;
            }
        }  // for
    }      // for
}

static int xor_weight(int w) {
    if (w == 1) {
        return 0;
    }

    //     int ow = w;
    int answer = 0;
    for (int i = 0; w != 1 && i < prime_cnt; i++) {
        while (w != 1 && w % prime[i] == 0) {
            w /= prime[i];
            answer = answer ^ prime[i];
        }  // while
    }      // for

    // printf("xor: %d -> %d\n", ow, answer);
    return answer;
}

static void initialize() {
    compute_primes();

    scanf("%d", &n);

    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);

        add_edge(u, v, xor_weight(w));
    }  // for
}

static bool marked[NMAX + 10];
static int dfs(int x, int xorsum) {
    marked[x] = true;

    int answer = 0;
    for (unsigned i = 0; i < G[x].size(); i++) {
        Edge *e = G[x][i];
        int v = e->either(x);

        if (!marked[v]) {
            answer += dfs(v, xorsum ^ e->w);
        }
    }  // for

    if (xorsum == 0) {
        answer++;
    }

    return answer;
}

static int dfs(int x) {
    memset(marked, false, sizeof(marked));
    return dfs(x, 0);
}

int main() {
    initialize();

    int answer = 0;
    for (int i = 1; i <= n; i++) {
        answer += dfs(i);
    }  // for

    printf("%d", answer - n);

    return 0;
}  // function main
