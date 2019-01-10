#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 1000000

static int n;
static int w[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) scanf("%d", w + i);
        bool ok = true;
        vector<int> stk;
        for (int i = 1; i <= n; i++) {
            if ((n & 1) && w[i] == n) continue;
            if (!stk.empty()) {
                if ((stk.back() + 1) / 2 == (w[i] + 1) / 2) stk.pop_back();
                else stk.push_back(w[i]);
            } else stk.push_back(w[i]);
        }
        if (!stk.empty()) ok = false;
        stk.clear();
        for (int i = 1; i <= n; i++) {
            if (w[i] == 1) continue;
            if ((n & 1) == 0 && w[i] == n) continue;
            if (!stk.empty()) {
                if (stk.back() / 2 == w[i] / 2) stk.pop_back();
                else stk.push_back(w[i]);
            } else stk.push_back(w[i]);
        }
        if (!stk.empty()) ok = false;
        puts(ok ? "Yes" : "No");
    }
    return 0;
}
