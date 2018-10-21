#include <climits>

#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

inline int cnt(int s) {
    return __builtin_popcount(s);
}

inline void show(int s, int n) {
    char buf[n + 1];
    buf[n] = 0;
    for (int i = 0; i < n; i++, s >>= 1)
        buf[i] = s & 1 ? '1' : '0';
    printf("%s\n", buf);
}

int main() {
    int n;
    cin >> n;
    int mask = (1 << n)  - 1;
    int best = INT_MIN;
    vector<int> sol;
    for (int s = 0; s < (1 << n); s++) {
        int worst = INT_MAX;
        for (int t = 0; t < (1 << n); t++)
            worst = min(
                worst,
                -cnt(s ^ t) * 2 + cnt(s & t) * 3 +
                cnt((~s) & (~t) & mask));
        if (worst > best) {
            best = worst;
            sol.clear();
        }
        if (worst >= best) sol.push_back(s);
    }
    printf("best = %d\n", best);
    for (int s : sol) show(s, n);

    return 0;
}
