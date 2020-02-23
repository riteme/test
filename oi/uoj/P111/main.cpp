#include <cstdio>
#include <cstring>

#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 30000
#define SMAX 30
#define INF 0x3f3f3f3f

static int n, m;
static vector<int> st[NMAX];
static int dist[SMAX + 1][NMAX];
static bool mark[SMAX + 1][NMAX];

struct State {
    int j, k, t;

    bool operator<(const State &z) const {
        return t > z.t;
    }
};

int main() {
    scanf("%d%d", &n, &m);
    int s, t;
    for (int i = 0; i < m; i++) {
        int j, k;
        scanf("%d%d", &j, &k);
        st[j].push_back(k);
        if (i == 0) s = j;
        if (i == 1) t = j;
    }

    memset(dist, 0x3f, sizeof(dist));
    dist[0][s] = 0;
    priority_queue<State> q;
    q.push({0, s, 0});
    while (!q.empty()) {
        auto _ = q.top();
        q.pop();
        int j = _.j, k = _.k, t = _.t;
        if (mark[j][k])
            continue;
        mark[j][k] = true;

        auto check = [&q](int j, int k, int t) {
            if (dist[j][k] > t) {
                dist[j][k] = t;
                q.push({j, k, t});
            }
        };
        if (j) {
            check(0, k, t);
            if (k - j >= 0) check(j, k - j, t + 1);
            if (k + j < n) check(j, k + j, t + 1);
        } else {
            for (int s : st[k]) {
                if (s <= SMAX) check(s, k, t);
                else {
                    for (int i = 1; k - i * s >= 0; i++)
                        check(0, k - i * s, t + i);
                    for (int i = 1; k + i * s < n; i++)
                        check(0, k + i * s, t + i);
                }
            }
        }
    }

    printf("%d\n", dist[0][t] < INF ? dist[0][t] : -1);
    return 0;
}
