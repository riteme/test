#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 8000;
constexpr int INF = 0x3f3f3f3f;

struct val {
    int d, c;

    void operator+=(const val &v) {
        if (d == -1 || v.d > d) {
            d = v.d;
            c = v.c;
        } else if (v.d != -1 && v.d == d) {
            c += v.c;
        }
    }

    bool operator<(const val &v) const {
        if (d == -1)
            return false;
        if (v.d == -1)
            return true;
        return d < v.d || (d == v.d && c < v.c);
    }
};

int n, q;
int cnt0[NMAX + 10];
int cnt1[NMAX + 10][NMAX + 10];
val f[NMAX + 10][NMAX + 10];

val solve(int l, int r) {
    // printf("(%d, %d)\n", l, r);
    if (l + 1 == r) {
        int c = cnt0[l] + cnt0[r] - cnt1[l][r];
        // printf("l=%d, r=%d, c=%d\n", l, r, c);
        f[l][r] = {
            .d = (c > 0 ? 0 : -1),
            .c = (c > 0 ? 0 : INF),
        };
        printf("f[%.1lf][%.1lf] = {d= %d, c= %d}\n", l * 0.5, r * 0.5, f[l][r].d, f[l][r].c);
        return f[l][r];
    }
    if (f[l][r].d != -1)
        return f[l][r];

    int best_k = 0;
    for (int k = l + 1; k < r; k += 2) {
        val u = {-1, 0};
        u += solve(l, k);
        u += solve(k + 1, r);
        if (u.d != -1)
            u.d++;
        if (u.d == 1) {
            u.c = cnt0[l] + cnt0[r] - cnt1[l][r];
        }
        if (u < f[l][r]) {
            f[l][r] = u;
            best_k = k;
        }
    }

    if (f[l][r].d == -1) {
        int c = cnt0[l] + cnt0[r] - cnt1[l][r];
        // printf("l=%d, r=%d, c=%d\n", l, r, c);
        f[l][r] = {
            .d = (c > 0 ? 0 : -1),
            .c = (c > 0 ? 0 : INF),
        };
    }

    printf("f[%.1lf][%.1lf] @%.1lf = {d= %d, c= %d}\n",
           l * 0.5,
           r * 0.5,
           best_k * 0.5,
           f[l][r].d,
           f[l][r].c);
    return f[l][r];
}

int main() {
    scanf("%d%d", &n, &q);
    while (q--) {
        int l, r;
        scanf("%d%d", &l, &r);
        cnt0[2 * l]++;
        cnt0[2 * r + 1]++;
        cnt1[2 * l][2 * r + 1]++;
    }

    for (int i = 2; i <= 2 * n; i += 2) {
        for (int j = 3; j <= 2 * n + 1; j += 2) {
            f[i][j].d = -1;
            f[i][j].c = 0;
        }
    }

    val v = solve(2, 2 * n + 1);
    // v.c = -v.c;
    // for (int k = 3; k <= 2 * n; k++) {
    //     v.c += cnt0[k];
    // }
    // v.c += cnt1[2][2 * n + 1];
    printf("%d %d\n", v.d, v.c);
    return 0;
}
