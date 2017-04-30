// #define NDEBUG

#include <cassert>
#include <cstring>
#include <cstdio>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n;
static int dfs[NMAX + 10];
static int pos[NMAX + 10];
static int bfs[NMAX + 10];
static double sum[NMAX + 10];
static vector<int> bucket[NMAX + 10];
static int cnt[NMAX + 10];

void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", dfs + i);
        pos[dfs[i]] = i;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", bfs + i);
        dfs[pos[bfs[i]]] = i;
    }

    for (int i = 1; i <= n; i++) {
        pos[dfs[i]] = i;
        sum[i] = 0.5;
    }
}

int main() {
    initialize();

    sum[1] = 1.0;
    for (int i = 2; i <= n - 1; i++) {
        if (pos[i] > pos[i + 1])
            sum[i] = 1.0;
        if (dfs[i] < dfs[i + 1])
            bucket[dfs[i + 1] - 1].push_back(dfs[i]);
    }

    int lastpos = 0;
    for (int r = 1; r <= n; r++) {
        if (sum[r] >= 1.0)
            lastpos = r;

        for (size_t i = 0; i < bucket[r].size(); i++) {
            int l = bucket[r][i];

            if (l <= lastpos) {
                cnt[l]++;
                cnt[r + 1]--;
            }
        }
    }

    for (int i = 1; i < n; i++) {
        cnt[i] += cnt[i - 1];

        if (cnt[i] && sum[i] < 1.0)
            sum[i] = 0.0;
    }

    double answer = 0.0;
    for (int i = 1; i < n; i++) {
        answer += sum[i];
    }

    printf("%.3lf\n", answer + 1.0);

    return 0;
}
