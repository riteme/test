#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

using i64 = long long;

constexpr int NMAX = 1000;
constexpr i64 INF = 1000000000000;

int n, m;
i64 a[NMAX + 10][NMAX + 10];
i64 row[NMAX + 10][NMAX + 10];
i64 col[NMAX + 10][NMAX + 10];

void left(int i, int &j, i64 &v) {
    v -= row[i][j];
    j--;
}

void right(int i, int &j, i64 &v) {
    j++;
    v += row[i][j];
}

void up(int &i, int j, i64 &v) {
    v -= col[i][j];
    i--;
}

void down(int &i, int j, i64 &v) {
    i++;
    v += col[i][j];
}

bool locate(i64 w) {
    int i = 0, j = 1;
    i64 v = 0;
    while (v < w) {
        down(i, j, v);
    }
    if (v == w)
        return true;
    while (i >= 0) {
        up(i, j, v);
        if (v == w)
            return true;
        while (j <= m) {
            right(i, j, v);
            if (v == w)
                return true;
            if (v > w) {
                left(i, j, v);
                break;
            }
            if (v == w)
                return true;
        }
    }
    return false;
}

void incr(int x, int y, i64 v) {
    for (int i = x; i <= n; i++) {
        row[i][y] += v;
    }
    for (int j = y; j <= m; j++) {
        col[x][j] += v;
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            scanf("%lld", &a[i][j]);
        }
    }

    n++;
    m++;
    for (int i = 1; i <= n; i++) {
        a[i][m] = INF;
    }
    for (int j = 1; j <= m; j++) {
        a[n][j] = INF;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            row[i][j] = a[i][j] - a[i][j - 1];
            col[i][j] = a[i][j] - a[i - 1][j];
        }
    }

    int q;
    scanf("%d", &q);
    while (q--) {
        int op;
        scanf("%d", &op);
        i64 v;
        if (op == 1) {
            scanf("%lld", &v);
            puts(locate(v) ? "1" : "0");
        } else {
            int x, y;
            scanf("%d%d%lld", &x, &y, &v);
            incr(x, y, v);
        }
    }

    return 0;
}
