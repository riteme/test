#include <cstdio>
#include <climits>

#include <algorithm>

using namespace std;

int main() {
    int T;
    scanf("%d", &T);
    for (int _t = 1; _t <= T; _t++) {
        int n, S;
        scanf("%d%d", &n, &S);
        int mx = INT_MIN;
        for (int i = 0; i < n; i++) {
            int f, t;
            scanf("%d%d", &f, &t);
            if (t <= S) mx = max(mx, f);
            else mx = max(mx, f - (t - S));
        }
        printf("Case #%d: %d\n", _t, mx);
    }
    return 0;
}