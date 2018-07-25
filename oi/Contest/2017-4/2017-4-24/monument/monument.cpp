// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000
#define EPSILON 0.0005

struct Owen {
    double x, v;

    bool operator<(const Owen &b) const {
        return x < b.x;
    }
};

static int n, K;
static Owen owen[NMAX + 10];
static double pos[NMAX + 10];
static int seq[NMAX + 10];

void initialize() {
    scanf("%d%d", &n, &K);

    for (int i = 1; i <= n; i++) {
        scanf("%lf%lf", &owen[i].x, &owen[i].v);
    }

    sort(owen + 1, owen + n + 1);
}

bool cmp(const int a, const int b) {
    return pos[a] < pos[b];
}

static int t;
static int bucket[NMAX + 10];

bool test(double L) {
    for (int i = 1; i <= n; i++) {
        pos[i] = owen[i].x + owen[i].v * L;
        seq[i] = i;
    }

    sort(seq + 1, seq + n + 1, cmp);
    
    t = 0;
    for (int i = 1; i <= n; i++) {
        int u = upper_bound(bucket, bucket + t + 1, seq[i]) - bucket - 1;

        if (u == t) {
            t++;
            bucket[t] = seq[i];
        } else
            bucket[u + 1] = min(bucket[u + 1], seq[i]);
    }

    return n - t <= K;
}

int main() {
#ifdef USE_FILE_IO
    freopen("monument.in", "r", stdin);
    freopen("monument.out", "w", stdout);
#endif
    initialize();

    double left = 0.0, right = 1e9 + 10;
    while (right - left > EPSILON) {
        double mid = (left + right) * 0.5;

        if (test(mid))
            left = mid;
        else
            right = mid;
    }

    if (left > 1e9)
        puts("Forever");
    else
        printf("%.8lf\n", left);

    return 0;
}
