#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

int b[NMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n; i++) {
            scanf("%d", b + i);
        }
        sort(b + 1, b + n + 1);
        int cnt = 0;
        b[n + 1] = -1;
        for (int a = 0; a <= n; a++) {
            auto i = upper_bound(b + 1, b + n + 1, a - 1);
            int A = (i - b) - 1;
            if (*i != a && A == a)
                cnt++;
        }
        printf("%d\n", cnt);
    }
    return 0;
}
