#pragma GCC optimize(3)

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long int64;

static int n, k;
static int64 dist[NMAX + 10];
static int64 tax[NMAX + 10];
static int64 f[NMAX + 10];
static vector<int> ok[NMAX + 10];

static void initialize() {
    scanf("%d%d", &n, &k);

    for (int i = 1; i <= n; i++)
        scanf("%lld", dist + i);
    for (int i = 0; i < n; i++)
        scanf("%lld", tax + i);
    for (int i = 1; i <= n; i++)
        dist[i] += dist[i - 1];
    for (int i = 0; i < n; i++) {
        int64 *iter = upper_bound(dist, dist + n + 1, tax[i] + dist[i]);
        int pos = iter - dist;
        ok[pos].push_back(i);
    }
}

int main() {
    freopen("empire.in", "r", stdin);
    freopen("empire.out", "w", stdout);
    initialize();

    deque<int> qtax;
    deque<int> qfee;
    if (tax[0] == 0)
        qfee.push_back(0);
    for (int i = 1; i <= n; i++) {
        for (size_t pos = 0; pos < ok[i].size(); pos++) {
            int u = ok[i][pos];

            if (u < i - k)
                continue;

            while (!qfee.empty() && 
                   f[qfee.back()] - dist[qfee.back()] > f[u] - dist[u])
                qfee.pop_back();

            if (qfee.empty() ||
                (f[qfee.back()] - dist[qfee.back()] <= f[u] - dist[u] &&
                 qfee.back() < u))
                 qfee.push_back(u);
        }

        while (!qtax.empty() && (tax[qtax.back()] < dist[i] - dist[qtax.back()] || f[qtax.back()] + tax[qtax.back()] >= f[i - 1] + tax[i - 1]))
            qtax.pop_back();
        qtax.push_back(i - 1);

        while (!qtax.empty() && qtax.front() < i - k)
            qtax.pop_front();
        while (!qfee.empty() && qfee.front() < i - k)
            qfee.pop_front();

        while (!qtax.empty() && tax[qtax.front()] < dist[i] - dist[qtax.front()])
            qtax.pop_front();

        f[i] = LLONG_MAX;

        if (!qtax.empty())
            f[i] = min(f[i],
                f[qtax.front()] + tax[qtax.front()]
            );
        if (!qfee.empty())
            f[i] = min(f[i],
                f[qfee.front()] + dist[i] - dist[qfee.front()]
            );

        assert(f[i] < LLONG_MAX);
    }

    printf("%lld\n", f[n]);

    return 0;
}
