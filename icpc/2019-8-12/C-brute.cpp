#include <cstdio>
#include <cstring>

#include <string>
#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, K;
static char str[NMAX + 10];

inline int calc(int l, int r) {
    int cnt = 0;
    auto it = str, ed = str + n + 1, lp = str;
    for ( ; it < ed; ) {
        it = search(it + 1, ed, str + l, str + r + 1);
        if (it < ed) {
            if (lp == str || it - lp > r - l + 1) cnt++;
            lp = it;
        }
    }
    return cnt;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s%d", str + 1, &K);
        n = strlen(str + 1);
        string ans;
        for (int i = 1; i <= n; i++) for (int j = i; j <= n; j++) {
            if (calc(i, j) == K) {
                string tmp;
                for (int k = i; k <= j; k++) tmp.push_back(str[k]);
                if (ans.empty() || tmp < ans) ans = tmp;
            }
        }
        if (ans.empty()) puts("-1");
        else printf("%s\n", ans.data());
    }
    return 0;
}
