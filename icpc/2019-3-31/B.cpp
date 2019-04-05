#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define rep(i, l, r) for (int i = (l); i < (r); i++)

typedef vector<string> Map;

static int n, m;
static Map G;
static Map O[2];

inline void transpose() {
    auto T = G;
    G.resize(m);
    rep(i, 0, m) G[i].resize(n);
    rep(i, 0, n) rep(j, 0, m) G[j][i] = T[i][j];
    swap(n, m);
}

inline int nxt(int a, int b, int c) {
    rep(r, 0, 3)
        if (a != r && b != r && c != r) return r;
    return 3;
}

inline int match(Map &D, int a, int b, int i) {
    int r = 0;
    for (int j = 0; j < n; j += 2) r += D[j][i] == a;
    for (int j = 1; j < n; j += 2) r += D[j][i] == b;
    return r;
}

int test(Map &D) {
    int ret = -1;
    rep(a, 0, 4) rep(b, 0, 4) if (a != b) {
        Map T;
        T.resize(n);
        rep(i, 0, n) T[i].resize(m);
        int sum = match(G, a, b, 0);
        rep(i, 0, n) T[i][0] = i & 1 ? b : a;
        rep(i, 1, m) {
            int na = T[0][i - 1], nb = T[1][i - 1];
            int cur = -1, nc;
            rep(c, 0, 4) if (na != c && nb != c) {
                int d = nxt(na, nb, c), val = match(G, c, d, i);
                if (val > cur) {
                    cur = val;
                    nc = c;
                }
            }
            sum += cur;
            int nd = nxt(na, nb, nc);
            rep(j, 0, n) T[j][i] = j & 1 ? nd : nc;
        }
        if (sum > ret) {
            ret = sum;
            D = T;
        }
    }

    return ret;
}

inline int toint(char c) {
    switch (c) {
        case 'A': return 0;
        case 'G': return 1;
        case 'C': return 2;
        default: return 3;
    }
}

int main() {
    cin >> n >> m;
    rep(i, 0, n) {
        static string buf;
        cin >> buf;
        rep(j, 0, m)
            buf[j] = toint(buf[j]);
        G.push_back(buf);
    }

    int v1 = test(O[0]);
    transpose();
    int v2 = test(O[1]);
    int p = v1 > v2 ? 0 : 1;
    G = O[p];
    if (p) transpose();
    else swap(n, m);
    constexpr char str[] = "AGCT";
    rep(i, 0, n) {
        rep(j, 0, m) putchar(str[G[i][j]]);
        puts("");
    }

    return 0;
}
