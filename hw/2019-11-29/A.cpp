#include <cstdio>
#include <cstring>

#include <queue>
#include <algorithm>

using namespace std;

void solve() {
    int _, n;
    scanf("%d%d", &_, &n);
    priority_queue<int> q;
    priority_queue<int, vector<int>, greater<int>> p;
    int cnt = 0;
    printf("%d %d\n", _, n / 2 + 1);
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        if (!q.empty() && v <= q.top()) q.push(v);
        else p.push(v);
        if (i % 2 == 0) {
            while (q.size() > i / 2 + 1) {
                p.push(q.top());
                q.pop();
            }
            while (q.size() < i / 2 + 1) {
                q.push(p.top());
                p.pop();
            }
            printf(cnt < 9 ? "%d " : "%d\n", q.top());
            cnt = (cnt + 1) % 10;
        }
    }
    if (cnt) puts("");
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
