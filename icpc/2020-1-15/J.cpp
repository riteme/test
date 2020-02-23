#include <cstdio>
#include <cstring>
#include <cassert>

#include <set>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

#define NMAX 200000
#define S 1000
#define BMAX (((NMAX) + (S) - 1) / (S) + 1)

#define INC 0
#define DEC 1
#define L 0
#define R 1

#define ID(x) (x / (S))
#define MAXID (n / (S))
#define LB(i) max(1, (i) * (S))
#define RB(i) min(n, ((i) + 1) * (S) - 1)

int n, q;
int h[NMAX + 10], hs[NMAX + 10];
vector<int> vec[BMAX + 10][2];
vector<int> seq[BMAX];
int nxt[NMAX + 10][2];

struct State {
    int u, t;

    State operator+(int k) const {
        return {u, t + k};
    }
} go[NMAX + 10][2];

void dp(int x) {
    for (int _i = 0; _i < seq[x].size(); _i++) {
        int i = seq[x][_i];
        if (nxt[i][L]) go[i][L] = go[nxt[i][L]][R] + 1;
        else go[i][L] = {-i, 0};
        if (nxt[i][R]) go[i][R] = go[nxt[i][R]][L] + 1;
        else go[i][R] = {-i, 0};
    }
}

void build_vec(int x) {
    auto &inc = vec[x][INC];
    inc.clear();
    for (int i = LB(x); i <= RB(x); i++)
        if (inc.empty() || h[i] > h[inc.back()]) inc.push_back(i);

    auto &dec = vec[x][DEC];
    dec.clear();
    for (int i = RB(x); i >= LB(x); i--)
        if (dec.empty() || h[i] > h[dec.back()]) dec.push_back(i);
}

void update(int i) {
    int id = ID(i), k;
    for (k = seq[id].size() - 1; k >= 0 && seq[id][k] != i; k--) ;
    assert(k >= 0);
    for ( ; k && h[i] > h[seq[id][k - 1]]; k--)
        swap(seq[id][k], seq[id][k - 1]);

    int j = i - 1;
    while (j >= LB(id) && h[j] < h[i]) j--;
    if (j >= LB(id)) nxt[i][L] = j;
    else nxt[i][L] = 0;

    j = i + 1;
    while (j <= RB(id) && h[j] < h[i]) j++;
    if (j <= RB(id)) nxt[i][R] = j;
    else nxt[i][R] = 0;

    for (j = LB(id); j < i; j++)
    if (h[j] < h[i] && (!nxt[j][R] || nxt[j][R] > i))
        nxt[j][R] = i;

    for (j = i + 1; j <= RB(id); j++)
    if (h[j] < h[i] && (!nxt[j][L] || nxt[j][L] < i))
        nxt[j][L] = i;

    dp(id);
}

int mx(int i) {
    return h[vec[i][INC].back()];
}

int query(int x, int d) {
    while (go[x][d].u < 0) {
        int v = -go[x][d].u;
        int t = d ^ (go[x][d].t & 1);

        int i = ID(x), j = i + (t == L ? -1 : 1);
        if (t == L)
            while (j >= 0 && mx(j) < h[v]) j--;
        else
            while (j <= MAXID && mx(j) < h[v]) j++;

        if (j < 0 || j > MAXID)
            return v;

        auto &li = vec[j][t == L ? DEC : INC];
        int l = 0, r = li.size() - 1;
        while (l < r) {
            int mi = (l + r) / 2;
            int p = li[mi];
            if (h[p] > h[v]) r = mi;
            else l = mi + 1;
        }

        d = t ^ 1;
        x = li[l];
    }

    return go[x][d].u;
}

void initialize() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%d", h + i);
        hs[i] = i;
    }

    set<int> li;
    li.insert(0);
    li.insert(n + 1);

    sort(hs + 1, hs + n + 1, [](int i, int j) {
        return h[i] > h[j];
    });
    for (int _i = 1; _i <= n; _i++) {
        int i = hs[_i];
        auto it = li.insert(i).first;
        auto p = prev(it);
        if (*p != 0 && ID(*p) == ID(i))
            nxt[i][L] = *p;
        p = next(it);
        if (*p != n + 1 && ID(*p) == ID(i))
            nxt[i][R] = *p;
    }

    for (int i = 0; i <= MAXID; i++) {
        for (int j = LB(i); j <= RB(i); j++)
            seq[i].push_back(j);
        sort(seq[i].begin(), seq[i].end(), [](int x, int y) {
            return h[x] > h[y];
        });

        dp(i);
        build_vec(i);
    }
}

int main() {
    initialize();

    char buf[16];
    int x, v;
    while (q--) {
        scanf("%s", buf);
        if (buf[0] == 'U') {
            scanf("%d%d", &x, &v);
            h[x] = v;
            update(x);
            build_vec(ID(x));
        } else {
            scanf("%d", &x);
            v = buf[0] == 'L' ? L : R;
            printf("%d\n", query(x, v));
        }
    }

    return 0;
}