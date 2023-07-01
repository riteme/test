#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <queue>

using namespace std;

using i64 = long long;

constexpr i64 INF = 0x3f3f3f3f3f3f3f3f;

int n;
int len[200];
char S[200][100];
i64 C[200];

int id(int rev, int i, int j) {
    return (rev << 16) | (i << 8) | j;
}

bool is_pal(const char *beg, const char *end) {
    while (beg < end) {
        if (*beg != *end)
            return false;
        beg++;
        end--;
    }
    return true;
}

constexpr int t = 0x1ffff;

i64 dist[1000000];

struct item {
    int u;
    i64 t;

    bool operator<(const item &z) const {
        return t > z.t;
    }
};

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%s%lld", S[i] + 1, C + i);
        len[i] = strlen(S[i] + 1);
    }

    i64 ans = LLONG_MAX;
    for (int i = 1; i <= n; i++) {
        if (is_pal(S[i] + 1, S[i] + len[i]))
            ans = min(ans, C[i]);
    }

    memset(dist, 0x3f, sizeof(dist));
    priority_queue<item> q;
    for (int i = 1; i <= n; i++) {
        int u = id(0, i, len[i]);
        dist[u] = C[i];
        q.push({u, C[i]});
    }

    auto up = [&](int v, i64 t) {
        if (dist[v] > t) {
            dist[v] = t;
            q.push({v, t});
        }
    };

    while (q.size()) {
        auto it = q.top();
        int u = it.u;
        q.pop();
        if (dist[u] != it.t)
            continue;
        if (u == t)
            break;

        int rev = u >> 16;
        int i = (u >> 8) & 0xff;
        int l = u & 0xff;

        if (l == 0)
            up(t, dist[u]);

        if (rev) {
            if (is_pal(S[i] + 1, S[i] + l))
                up(t, dist[u]);
        } else {
            if (is_pal(S[i] + len[i] - l + 1, S[i] + len[i]))
                up(t, dist[u]);
        }

        for (int j = 1; j <= n; j++) {
            int k = 0;
            for (; k < l && k < len[j]; k++) {
                if (rev) {
                    if (S[i][l - k] != S[j][1 + k])
                        break;
                } else {
                    if (S[i][len[i] - l + 1 + k] != S[j][len[j] - k])
                        break;
                }
            }

            if (k == l) {
                int v = id(rev ^ 1, j, len[j] - l);
                up(v, dist[u] + C[j]);
            }
            if (k == len[j]) {
                int v = id(rev, i, l - len[j]);
                up(v, dist[u] + C[j]);
            }
        }
    }

    ans = min(ans, dist[t]);
    if (ans >= INF)
        ans = -1;
    printf("%lld\n", ans);

    return 0;
}
