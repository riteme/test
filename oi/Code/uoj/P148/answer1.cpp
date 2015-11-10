#include <iostream>
#include <cstdio>
using namespace std;
int l, L, n, m, stone[60000];
int main() {
    cin >> L >> n >> m;
    for (int i = 1; i <= n; i++) cin >> stone[i];
    int l = 1, r = L;
    while (l < r) {
        int a, k, t;
        a = 0;
        t = 0;
        k = (l + r + 1) / 2;
        for (int i = 1; i <= n; ++i) {
            if (stone[i] - a >= k)
                a = stone[i];
            else
                ++t;
        }
        if (L - a < k) ++t;
        if (t <= m)
            l = k;
        else
            r = k - 1;
    }
    cout << l;
}
