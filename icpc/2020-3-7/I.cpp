#include <cstdio>
#include <cstring>

#include <set>
#include <queue>
#include <algorithm>
#include <tr1/unordered_map>

using namespace std;

#define NMAX 100000

int n, m;
int a[NMAX + 10], nxt[NMAX + 10];

void solve() {
    tr1::unordered_map<int, int> lp;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        lp[a[i]] = n + a[i];
    }
    for (int i = 1; i <= m; i++)
        lp[i] = n + i;

    for (int i = n; i >= 1; i--) {
        nxt[i] = lp[a[i]];
        lp[a[i]] = i;
    }

    set<int> q;
    for (int i = 1; i <= m; i++)
        q.insert(lp[i]);

    int cnt = 0;
    for (int i = 1; i <= n; i++)
    if (q.count(i)) {
        q.erase(i);
        q.insert(nxt[i]);
    } else {
        cnt++;
        q.insert(nxt[i]);
        q.erase(--q.end());
    }

    printf("%d\n", cnt);
}

int main() {
    while (scanf("%d%d", &n, &m) != EOF) {
        solve();
    }
    return 0;
}