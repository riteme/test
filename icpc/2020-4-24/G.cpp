#include <cstdio>
#include <cstring>

#include <map>
#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

int n;
map<int, int> seq;
int lch[NMAX + 10], rch[NMAX + 10];

int cnt = 0;
void print(int x) {
    if (!x)
        return;
    if (0 < x && x <= n) {
        cnt++;
        printf(cnt < n ? "%d " : "%d\n", x);
    }
    print(lch[x]);
    print(rch[x]);
}

void solve() {
    memset(lch + 1, 0, sizeof(int) * n);
    memset(rch + 1, 0, sizeof(int) * n);
    seq.clear();
    seq[0] = -1;
    seq[n + 1] = 0;

    for (int i = 0; i < n; i++) {
        int u;
        scanf("%d", &u);
        auto r = seq.upper_bound(u);
        auto l = prev(r);
        auto p = r->second > l->second ? r : l;
        seq[u] = p->second + 1;
        if (p->first < u)
            rch[p->first] = u;
        else
            lch[p->first] = u;
    }

    cnt = 0;
    print(n + 1);
}

int main() {
    while (scanf("%d", &n) != EOF)
        solve();

    return 0;
}