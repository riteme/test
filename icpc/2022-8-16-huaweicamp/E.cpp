#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 100000;
constexpr int S = 500;
constexpr int L = 24;
constexpr int BMAX = NMAX / S + 1;

int n, q;
int a[NMAX + S + 10];
int off[BMAX + 10][L];
int ln[NMAX + S + 10], re[NMAX + S + 10];

void modify(int i, int v) {
    a[i] = v;
    int b = i / S;
    int l = b * S;
    int r = l + S;
    for (int j = 0; j < L; j++) {
        int w = j;
        int k = l;
        while (a[k] <= w) {
            w -= a[k];
            k++;
        }
        off[b][j] = k;
    }
    int k = r;
    int w = 0;
    for (int j = r - 1; j >= l; j--) {
        w += a[j];
        while (w > L) {
            w -= a[--k];
        }
        if (k >= r) {
            ln[j] = 1;
            re[j] = L - w;
        } else {
            ln[j] = 1 + ln[k];
            re[j] = re[k];
        }
    }
}

int query(int x, int y) {
    int c = 0, w = 0;
    auto step = [&](int i) {
        if (a[i] > w) {
            c++;
            w = L;
        }
        w -= a[i];
    };
    int i = x;
    int xb = x / S;
    int xr = (xb + 1) * S;
    for ( ; i <= y && i < xr; i++) {
        step(i);
    }
    int yb = y / S;
    for ( ; i < yb * S; i += S) {
        int j = off[i / S][w];
        c += ln[j];
        w = re[j];
    }
    for ( ; i <= y; i++) {
        step(i);
    }
    return c;
}

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 0; i <= n + S; i++) {
        a[i] = L;
    }
    for (int i = 1; i <= n; i++) {
        int v;
        scanf("%d", &v);
        modify(i, v);
    }
    while (q--) {
        int op, a, b;
        scanf("%d%d%d", &op, &a, &b);
        if (op == 1)
            modify(a, b);
        else
            printf("%d\n", query(a, b));
    }

    return 0;
}
