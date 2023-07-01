#include <cstdio>
#include <cstring>

#include <algorithm>
#include <map>

using namespace std;

int n;
map<int, int> cnt;

void solve() {
    cnt.clear();
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int v;
        scanf("%d", &v);
        cnt[v]++;
    }
    if (cnt[0] * 2 <= n + 1) {
        puts("0");
    } else if (cnt[1] == 0) {
        puts("1");
    } else if (cnt.size() > 2) {
        puts("1");
    } else {
        puts("2");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        solve();
    }
    return 0;
}
