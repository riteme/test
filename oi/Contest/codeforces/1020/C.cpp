#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

#define NMAX 3000

static int n, m, seq[NMAX + 10];
static i64 cost[NMAX + 10];
static int marked[NMAX + 10];
static vector<int> vot[NMAX + 10];

bool cmp1(int x, int y) {
    return cost[x] > cost[y];
}

bool cmp2(int x, int y) {
    return cost[x] < cost[y];
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int p;
        scanf("%d%lld", &p, cost + i);
        seq[i] = i;
        vot[p].push_back(i);
    }

    sort(seq + 1, seq + n + 1, cmp2);
    for (int i = 2; i <= m; i++)
        sort(vot[i].begin(), vot[i].end(), cmp1);

    i64 ans = 1e18;
    for (int i = 0; i < n; i++) {
        memset(marked, 0, sizeof(marked));
        for (int j = 2; j <= m; j++) {
            int c = 0;
            for (int k = 0; k < vot[j].size(); k++) {
                if (c >= i) break;
                int x = vot[j][k];
                if (marked[x]) continue;
                marked[x] = 1;
                c++;
            }
        }

        i64 sum = 0;
        int c = vot[1].size();
        for (int j = 0; j < vot[1].size(); j++)
            marked[vot[1][j]] = 2;
        for (int j = 1; j <= n; j++) {
            int x = seq[j];
            if (marked[x]) continue;
            sum += cost[x];
            c++;
        }

        for (int j = 1; c <= i && j <= n; j++) {
            int x = seq[j];
            if (marked[x] != 1) continue;
            sum += cost[x];
            c++;
        }

        if (sum < ans) ans = sum;
    }

    printf("%lld\n", ans);
    return 0;
}
