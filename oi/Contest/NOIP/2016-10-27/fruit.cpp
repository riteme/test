#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <algorithm>

#define NMAX 500
#define MMAX 30000
#define TMAX 1000000

static int n, m;
static int X[MMAX + 10];
static int T[MMAX + 10];
static int f[MMAX + 10];
static int sorted[MMAX + 10];
static int next[MMAX + 10];
static int prev[MMAX + 10];
static int last[NMAX + 10];
static int head[NMAX + 10];

static bool cmp(const int a, const int b) {
    return T[a] < T[b];
}

static void initialize() {
    scanf("%d%d", &n, &m);

    for (int i = 1; i <= m; i++) {
        scanf("%d", X + i);

        sorted[i] = i;
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d", T + i);
    }

    std::sort(sorted + 1, sorted + m + 1, cmp);
}

int main() {
    freopen("fruit.in", "r", stdin);
    freopen("fruit.out", "w", stdout);
    initialize();

    for (int i = 1; i <= m; i++) {
        f[i] = 1;

        int p = sorted[i];

        if (last[X[p]]) { 
            prev[p] = last[X[p]];
            next[last[X[p]]] = p;
        }

        last[X[p]] = p;
    }

    head[X[sorted[1]]] = sorted[1];
    for (int i = 2; i <= m; i++) {
        int p = sorted[i];
        
        for (int j = 1; j <= n; j++) {
            int t = T[p] - abs(j - X[p]);

            if (j == X[p])
                t--;

            if (t < 1)
                continue;

            int lasth = head[j];
            while (T[head[j]] > t) {
                lasth = head[j];
                head[j] = prev[head[j]];
            }

            while (next[head[j]] != 0 && T[next[head[j]]] <= t)
                head[j] = next[head[j]];

            if (head[j])
                f[p] = std::max(f[p], f[head[j]] + 1);
            else
                head[j] = lasth;
        }

        head[X[p]] = p;
    }

    int answer = 0;
    for (int i = 1; i <= m; i++)
        answer = std::max(answer, f[i]);
    
    printf("%d\n", answer);

    return 0;
}
