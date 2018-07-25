#include <cstdio>

#include <algorithm>

using namespace std;

#define NMAX 200

typedef long long int64;

static int64 d;
static int64 n;
static int64 map[NMAX + 10][NMAX + 10];

inline int64 query(int l, int r, int t, int b) {
    int64 answer = 0;
    for (int i = max(0, l); i <= min(129, r); i++) {
        for (int j = max(0, t); j <= min(129, b); j++) {
            answer += map[i][j];
        }
    }

    return answer;
}

int main() {
    scanf("%lld%lld", &d, &n);

    for (int i = 1; i <= n; i++) {
        int x, y;
        int64 k;
        scanf("%d%d%lld", &x, &y, &k);

        map[x][y] += k;
    }

    int64 maxv = 0;
    for (int i = 0; i <= 128; i++) {
        for (int j = 0; j <= 128; j++) {
            maxv = max(maxv, query(i - d, i + d, j - d, j + d));
        }
    }

    int64 cnt = 0;
    for (int i = 0; i <= 128; i++) {
        for (int j = 0; j <= 128; j++) {
            if (query(i - d, i + d, j - d, j + d) == maxv)
                cnt++;
        }
    }

    printf("%lld %lld\n", cnt, maxv);
    return 0;
}
