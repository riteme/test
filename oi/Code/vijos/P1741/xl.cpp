#include <cstdio>
#include <cstring>
#include <climits>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000
#define MMAX 10000
#define KMAX 100000

static int n, m, k;
static int dist[NMAX + 10];
static int timestamp[MMAX + 10];
static int from[MMAX + 10];
static int to[MMAX + 10];

static int setoff[NMAX + 10];
static int latest[NMAX + 10];
static int endcnt[NMAX + 10];
static int right[NMAX + 10];
static vector<int> off[NMAX + 10];
static int offtime[MMAX + 10];

static void initialize() {
    scanf("%d%d%d", &n, &m, &k);

    for (int i = 1; i < n; i++)
        scanf("%d", dist + i);

    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d", timestamp + i, from + i, to + i);

        latest[from[i]] = max(latest[from[i]], timestamp[i]);
        endcnt[to[i]]++;
        off[to[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++)
        endcnt[i] += endcnt[i - 1];
}

int main() {
    initialize();

    setoff[1] = latest[1];
    for (int i = 2; i <= n; i++) {
        for (size_t pos = 0; pos < off[i].size(); pos++)
            offtime[off[i][pos]] = setoff[i - 1] + dist[i - 1];

        setoff[i] = max(setoff[i - 1] + dist[i - 1], latest[i]);
    }

    int answer = 0;
    for (int i = 1; i <= m; i++)
        answer += offtime[i] - timestamp[i];

    int j = 1;
    for (int i = 1; i < n; i++) {
        j = max(i + 1, j);
        while (j < n && setoff[j] > latest[j])
            j++;

        right[i] = j;
    }

    while (k--) {
        int opt = 0;
        int pos;
        for (int i = 1; i < n; i++) {
            if (dist[i] == 0)
                continue;

            int value = endcnt[right[i]] - endcnt[i];

            if (value > opt) {
                opt = value;
                pos = i;
            }
        }

        if (opt == 0)
            break;
        answer -= opt;
        dist[pos]--;

        for (int i = pos + 1; i <= n; i++)
            setoff[i] = max(setoff[i - 1] + dist[i - 1], latest[i]);

        j = 2;
        for (int i = 1; i < n; i++) {
            j = max(i + 1, j);
            while (j < n && setoff[j] > latest[j])
                j++;

            right[i] = j;
        }
    }

    printf("%d\n", answer);

    return 0;
}
