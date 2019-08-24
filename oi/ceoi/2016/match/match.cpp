// #define NDEBUG

#include <cassert>
#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

static vector<int> stk;
static int n;
static char s[NMAX + 10];
static bool right[NMAX + 10];
static int pre[NMAX + 10][256];

inline void chkmax(int &dest, int src) {
    if (src > dest)
        dest = src;
}

void initialize() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
}

void solve(int l, int r) {
    if (r < l)
        return;
    if (s[l] == s[r]) {
        right[r] = true;
        solve(l + 1, r - 1);
    } else {
        int mid = pre[r][s[l]];
        right[mid] = true;
        solve(l + 1, mid - 1);
        solve(mid + 1, r);
    }
}

int main() {
#ifdef USE_FILE_IO
    freopen("match.in", "r", stdin);
    freopen("match.out", "w", stdout);
#endif
    initialize();

    int last = 0;
    for (int i = n; i >= 1; i--) {
        if (last)
            chkmax(pre[last][s[i]], i);

        if (!stk.empty() && s[stk.back()] == s[i]) {
            last = stk.back();
            stk.pop_back();
        } else {
            stk.push_back(i);
        }
    }

    solve(1, n);

    for (int i = 1; i <= n; i++) {
        putchar(right[i] ? ')' : '(');
    }
    putchar('\n');

    return 0;
}
