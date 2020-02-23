#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define mxn 200
#define MXL 1e99

double e[mxn][mxn], l[mxn], r[mxn], s[mxn]; // e[][] <- -MXL
int p[mxn], f[mxn]; bool v[mxn];
double km(int n, int m) { // mathcing p[R] = L
    fill(p, p + m + 1, 0);
    fill(r, r + m + 1, 0);
    for (int i = 1; i <= n; ++i)
        r[0] -= l[i] = *max_element(e[i] + 1, e[i] + m + 1);
    for (int i = 1; i <= n; ++i) {
        fill(s, s + m + 1, MXL * 2);
        fill(v, v + m + 1, false);
        int y = 0, t; p[0] = i;
        do {
            v[y] = true; int x = p[y]; double d = MXL * 2;
            for (int j = 1; j <= m; ++j) if (!v[j]) {
                double c = l[x] + r[j] - e[x][j];
                if (c < s[j]) s[j] = c, f[j] = y;
                if (s[j] < d) d = s[j], t = j;
            }
            if (e[p[f[t]]][t] == -MXL) return -MXL; // no matching
            for (int j = 0; j <= m; ++j)
                if (v[j]) l[p[j]] -= d, r[j] += d; else s[j] -= d;
        } while (p[y = t]);
    while (y) p[y] = p[f[y]], y = f[y];
    }
    return -r[0];
}

double tb[200];

int main() {
    for (int i = 1; i <= 100; i++)
        tb[i] = log(i);

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    for (int j = 1; j <= n; j++) {
        int p;
        scanf("%d", &p);
        e[i][j] = tb[p];
    }
    km(n, n);
    for (int i = 1; i <= n; i++)
        printf("%d ", p[i]);
    puts("");
    return 0;
}