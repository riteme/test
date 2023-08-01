#pragma GCC optimize(3)

#include <cmath>
#include <cstdio>
#include <cstring>

#include <algorithm>
#include <vector>

using namespace std;

constexpr int NMAX = 400000;
constexpr int SMAX = 27;
constexpr char c0 = '`';

bool valid[NMAX + 10];

namespace PAM {

struct node {
    int len, fail, ch[SMAX];
    vector<int> failch;
    vector<int> tags;
} pam[NMAX * 3];

int n;
char s[NMAX + 10];
int p = 2, tot = 2, pos, idcnt = 1;

void extend() {
    int x = s[pos] - c0;
    if (x == 0) {
        idcnt++;
        p = 2;
        return;
    }

    while (s[pos - pam[p].len - 1] != s[pos])
        p = pam[p].fail;
    if (pam[p].ch[x])
        p = pam[p].ch[x];
    else {
        int np = ++tot;
        pam[p].ch[x] = np;
        pam[np].len = pam[p].len + 2;
        if (p == 1)
            pam[np].fail = 2;
        else {
            for (p = pam[p].fail; s[pos - pam[p].len - 1] != s[pos]; p = pam[p].fail)
                ;
            pam[np].fail = pam[p].ch[x];
        }
        p = np;
    }
    // printf("pos=%d idcnt=%d p=%d\n", pos, idcnt, p);
    if (x != 0)
        pam[p].tags.push_back(idcnt);
}

void scan_failch(int u) {
    // printf("pam[%d].fail= %d\n", u, pam[u].fail);
    if (pam[u].fail)
        pam[pam[u].fail].failch.push_back(u);
    for (int c = 0; c < SMAX; c++) {
        if (pam[u].ch[c])
            scan_failch(pam[u].ch[c]);
    }
}

void scan_tags(int u) {
    for (int v : pam[u].failch) {
        // printf("%d -> %d\n", u, v);
        scan_tags(v);
        pam[u].tags.insert(pam[u].tags.end(), pam[v].tags.begin(), pam[v].tags.end());
    }
    sort(pam[u].tags.begin(), pam[u].tags.end());
    pam[u].tags.erase(unique(pam[u].tags.begin(), pam[u].tags.end()), pam[u].tags.end());
}

void scan_valid(int u) {
    valid[u] = true;
    for (int c = 0; c < SMAX; c++) {
        int v = pam[u].ch[c];
        if (!v)
            continue;
        scan_valid(v);
    }
}

}  // namespace PAM

constexpr int IDMAX = 100000;

int ans[IDMAX + 10];

struct edge {
    int v;
    int &ans;
};

int n, m, Q, K;
int deg[IDMAX + 10];
vector<edge *> G[IDMAX + 10];
vector<int> setid[IDMAX + 10];
int cnt[IDMAX + 10];

int main() {
    scanf("%d%d", &n, &Q);
    int pos = 1;
    for (int i = 1; i <= n; i++) {
        scanf("%s", PAM::s + pos);
        pos += strlen(PAM::s + pos);
        PAM::s[pos++] = c0;
    }

    PAM::n = pos - 2;
    PAM::pam[1].len = -1;
    PAM::pam[2].fail = 1;
    for (PAM::pos = 1; PAM::pos <= PAM::n; PAM::pos++) {
        PAM::extend();
    }

    for (int i = 1; i <= Q; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        auto e = new edge{v, ans[i]};
        G[u].push_back(e);
        deg[u]++;
    }

    PAM::scan_failch(1);
    PAM::scan_failch(2);
    PAM::scan_tags(1);
    PAM::scan_valid(1);
    PAM::scan_valid(2);
    valid[1] = valid[2] = false;

    m = PAM::tot;
    for (int i = 1; i <= m; i++) {
        if (!valid[i])
            continue;

        // printf("T[%d]", i);
        for (int x : PAM::pam[i].tags) {
            setid[x].push_back(i);
            // printf(" %d", x);
        }
        // puts("");
    }

    K = max(2, int(sqrt(Q)));

    for (int i = 1; i <= n; i++) {
        if (deg[i] <= K)
            continue;

        for (int x : setid[i]) {
            for (int y : PAM::pam[x].tags) {
                cnt[y]++;
            }
        }

        for (auto e : G[i]) {
            e->ans = cnt[e->v];
        }
        memset(cnt, 0, sizeof(cnt));
    }

    for (int i = 1; i <= m; i++) {
        if (!valid[i])
            continue;

        auto &T = PAM::pam[i].tags;
        for (int x : T)
            cnt[x] = 1;
        for (int x : T) {
            if (deg[x] > K)
                continue;

            for (auto e : G[x]) {
                e->ans += cnt[e->v];
            }
        }
        for (int x : T)
            cnt[x] = 0;
    }

    for (int i = 1; i <= Q; i++) {
        printf("%d\n", ans[i]);
    }

    return 0;
}
