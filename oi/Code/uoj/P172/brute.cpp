// BRUTE FORCE
// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <queue>
#include <algorithm>

using namespace std;

#define NMAX 500000

typedef long long i64;

static int n;
static i64 L;
static char s[NMAX + 10];
static int fail[NMAX + 10];
static int cnt;
static int minbroder;
static int broder[NMAX + 10];
static bool exist[NMAX + 10];
static i64 dist[NMAX + 10];
static int bucket[NMAX + 10];

void initialize() {
    scanf("%d%lld%s", &n, &L, s + 1);
    L -= n;

    int j = fail[1] = 0;
    for (int i = 2; i <= n; i++) {
        while (j && s[j + 1] != s[i]) {
            j = fail[j];
        }

        if (s[j + 1] == s[i])
            j++;

        fail[i] = j;
    }

    cnt = 1;
    broder[1] = n;
    minbroder = n;
    int x = fail[n];
    while (x) {
        minbroder = min(minbroder, n - x);
        broder[++cnt] = n - x;
        x = fail[x];
    }

    memset(bucket, 0x3f, sizeof(bucket));
    
    for (int i = 1; i <= cnt; i++) {
        int w = broder[i];
        int pos = w % minbroder;
        bucket[pos] = min(bucket[pos], w);
    }

    cnt = 0;
    for (int i = 0; i < n; i++) {
        if (bucket[i] != 0x3f3f3f3f)
            broder[++cnt] = bucket[i];
    }

    n = minbroder;
}

void spfa() {

    for (int i = 1; i < n; i++) {
        dist[i] = LLONG_MAX;
    }

    queue<int> q;
    q.push(0);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        exist[u] = false;

        for (int i = 1; i <= cnt; i++) {
            int w = broder[i];
            int v = (u + w) % n;

            if (dist[v] > dist[u] + w) {
                dist[v] = dist[u] + w;

                if (!exist[v]) {
                    exist[v] = true;
                    q.push(v);
                }
            }
        }
    }
}

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        initialize();
        spfa();

        i64 answer = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] <= L)
                answer += 1 + (L - dist[i]) / n;
        }

        printf("%lld\n", answer);
    }

    return 0;
}
