#pragma GCC optimize(3)
#include <cstdio>
#include <cstring>

#include <set>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

constexpr int S = 26;
constexpr int NMAX = 2100000;
constexpr int INF = 0x3f3f3f3f;

void add(int &a, int &b, int c) {
    if (c < a) {
        b = a;
        a = c;
    } else if (a < c && c < b) {
        b = c;
    }
}

struct SAM {
    int mcnt;
    struct Node {
        int maxlen, fail;
        int first;
        int ch[S];
    } m[NMAX + 10];
    void reset() {
        memset(m, 0, sizeof(m));
        mcnt = 1;
        m[0].maxlen = -1;
        fill(m[0].ch, m[0].ch + S, 1);
    }

    int append(int x, int c) {
        int y = ++mcnt;
        m[y].first = m[y].maxlen = m[x].maxlen + 1;
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

    vector<int> G[NMAX + 10];
    vector<int> ins[NMAX + 10], del[NMAX + 10];
    int fi[NMAX + 10], se[NMAX + 10];

    void build_fail() {
        for (int i = 1; i <= mcnt; i++) {
            /*
            for (int c = 0; c < S; c++) {
                if (m[i].ch[c]) {
                    printf("%d %c-> %d\n", i, 'a' + c, m[i].ch[c]);
                }
            }
            */
            fi[i] = INF;
            se[i] = INF;

            if (i == 1)
                continue;

            int p = m[i].fail;
            /*
            printf("%d -> %d: maxlen=%d, first=%d\n",
                p, i, m[i].maxlen, m[i].first);
            */

            G[p].push_back(i);
        }
    }

    void dfs(int x) {
        for (int v : G[x]) {
            dfs(v);
            add(fi[x], se[x], m[v].first);
            add(fi[x], se[x], fi[v]);
            add(fi[x], se[x], se[v]);
        }
    }

    void solve(int n) {
        build_fail();
        dfs(1);
        for (int i = 2; i <= mcnt; i++) {
            int l = m[i].first;
            //int r = min(n, min_first[i] - 1);
            int r = n;
            if (m[i].first == fi[i])
                r = min(r, se[i] - 1);
            else
                r = min(r, fi[i] - 1);

            if (r < l)
                continue;

            int L = m[m[i].fail].maxlen + 1;
            //printf("[%d, %d]: %d\n", l, r, L);
            ins[l].push_back(L);
            del[r].push_back(L);
        }

        multiset<int> q;
        for (int i = 1; i <= n; i++) {
            for (int v : ins[i]) {
                q.insert(v);
            }

            int ans = q.size() ? *q.begin() : i;
            printf("%d\n", ans);

            for (int v : del[i]) {
                auto it = q.find(v);
                q.erase(it);
            }
        }
    }
} sam;

int n;
char s[NMAX + 10];

int main() {
    sam.reset();
    scanf("%d%s", &n, s + 1);
    int x = 1;
    for (int i = 1; i <= n; i++) {
        x = sam.append(x, s[i] - 'a');
    }
    sam.solve(n);

    return 0;
}
