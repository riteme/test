#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

constexpr int NMAX = 150;
constexpr int CMAX = 26;

struct SAM {
    int mcnt;
    struct Node {
        int maxlen, fail;  // basic
        int ch[CMAX];
    } m[3 * NMAX + 10];
    void reset() {
        memset(this, 0, sizeof(SAM));
        mcnt = 1;  // x = 1 the root
        // ease x = 0 case
        m[0].maxlen = -1;
        fill(m[0].ch, m[0].ch + CMAX, 1);
    }
    int append(int x, int c) {
        int y = ++mcnt;
        while (!m[x].ch[c]) {
            m[x].ch[c] = y;
            x = m[x].fail;
        }
        int p = m[x].ch[c];
        if (m[x].maxlen + 1 != m[p].maxlen) {
            int q = ++mcnt;
            m[q] = m[p];
            m[q].maxlen = m[x].maxlen + 1;
            m[p].fail = m[y].fail = q;
            while (m[x].ch[c] == p) {
                m[x].ch[c] = q;
                x = m[x].fail;
            }
        } else
            m[y].fail = p;
        return y;
    }
    Node &operator[](int i) {
        return m[i];
    }
} sam;

int n, L, K;
char s[NMAX + 10];
bool f[NMAX + 10][NMAX + 10][3 * NMAX + 10];

struct pos {
    int k, x;
};

void solve() {
    scanf("%d%d%d%s", &n, &L, &K, s);
    sam.reset();
    int x = 1;
    for (int i = 0; i < n;  i++) {
        x = sam.append(x, s[i] - 'a');
    }

    for (int l = 0; l <= L; l++) {
        for (int k = 0; k <= K; k++) {
            memset(f[l][k], 0, sizeof(int) * (sam.mcnt + 1));
        }
    }
    for (int x = 1; x <= sam.mcnt; x++) {
        f[L][K][x] = true;
    }

    for (int l = L - 1; l >= 0; l--) {
        for (int k = 0; k <= K; k++) {
            for (int x = 1; x <= sam.mcnt; x++) {
                for (int c = 0; c < CMAX; c++) {
                    if (sam[x].ch[c]) {
                        f[l][k][x] |= f[l + 1][k][sam[x].ch[c]];
                    } else if (sam[1].ch[c] && k < K) {
                        f[l][k][x] |= f[l + 1][k + 1][sam[1].ch[c]];
                    }
                }
            }
        }
    }

    if (!f[0][1][1]) {
        puts("-1");
        return;
    }

    vector<pos> q;
    vector<pos> buc[CMAX];
    q.push_back({1, 1});
    for (int l = 1; l <= L; l++) {
        for (int c = 0; c < CMAX; c++) {
            buc[c].clear();
        }

        for (auto [k, x] : q) {
            for (int c = 0; c < CMAX; c++) {
                int y = sam[x].ch[c];
                if (y) {
                    if (f[l][k][y])
                        buc[c].push_back({k, y});
                } else {
                    y = sam[1].ch[c];
                    if (y && k < K && f[l][k + 1][y]) {
                        buc[c].push_back({k + 1, y});
                    }
                }
            }
        }

        for (int c = 0; c < CMAX; c++) {
            if (buc[c].size()) {
                putchar('a' + c);
                q = std::move(buc[c]);
                break;
            }
        }
    }
    puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
