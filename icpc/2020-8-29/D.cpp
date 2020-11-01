#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

#define NMAX 100000
#define LOGN 20

int n;
i64 w;
i64 a[LOGN][NMAX + 10];
int _lg[NMAX + 10];

i64 query(int l, int r) {
    int k = _lg[r - l + 1];
    return max(a[k][l], a[k][r - (1 << k) + 1]);
}

int main() {
    scanf("%d%lld", &n, &w);
    for (int i = 2; i <= n; i++) {
        _lg[i] = _lg[i >> 1] + 1;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", a[0] + i);
    }
    for (int j = 1; j < LOGN; j++)
    for (int i = 1; i <= n; i++) {
        int k = i + (1 << (j - 1));
        if (k <= n)
            a[j][i] = max(a[j - 1][i], a[j - 1][k]);
        else
            a[j][i] = a[j - 1][i];
    }

    i64 l;
    for (l = 1; l <= n; l++) {
        i64 s = -1;
        for (int i = 1; i <= n; i += l) {
            s += 1 + query(i, min((i64) n, i + l - 1));
        }
        if (s <= w)
            break;
    }

    printf("%lld\n", l);
    return 0;
}
