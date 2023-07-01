#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

constexpr int NMAX = 200000;

using i64 = long long;

int m;
int a[NMAX + 10];
char s[NMAX + 10];
i64 prem[NMAX + 10][3];
i64 sufx[NMAX + 10][3];

int main() {
    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", a + i);
    }
    scanf("%s", s + 1);

    for (int i = 1; i <= m; i++) {
        memcpy(prem[i], prem[i - 1], sizeof(prem[i]));
        if (s[i] == 'M')
            prem[i][a[i]]++;
    }
    for (int i = m; i >= 1; i--) {
        memcpy(sufx[i], sufx[i + 1], sizeof(sufx[i]));
        if (s[i] == 'X')
            sufx[i][a[i]]++;
    }

    i64 ans = 0;
    for (int i = 1; i <= m; i++) {
        if (s[i] != 'E')
            continue;

        int c[3] = {a[i]};
        for (int u = 0; u < 3; u++) {
            for (int v = 0; v < 3; v++) {
                c[1] = u;
                c[2] = v;
                int m = 0;
                for (int j = 0; j < 3; j++) {
                    if (find(c, c + 3, m) != c + 3)
                        m++;
                }
                ans += prem[i - 1][u] * sufx[i + 1][v] * m;
            }
        }
    }
    printf("%lld\n", ans);
    return 0;
}
