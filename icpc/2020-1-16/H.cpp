#include <cstdio>
#include <cstring>

#include <unordered_map>
#include <algorithm>

using namespace std;

#define NMAX 3000

typedef long long i64;

int n;
i64 a[NMAX + 10];
unordered_map<i64, int> mp[NMAX + 10];
bool m[NMAX + 10][NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);

    for (int i = 1; i <= n; i++) {
        mp[i].reserve(n - i);
        for (int j = i + 1; j <= n; j++)
            mp[i][a[j] - a[i]] = j;
    }

    int ans = 2;
    for (int i = 1; i <= n; i++)
    for (int j = i + 1; j <= n; j++) if (!m[i][j]) {
        int len = 2, x = j;
        i64 d = a[j] - a[i];
        while (true) {
            auto it = mp[x].find(d);
            if (it == mp[x].end())
                break;
            len++;
            m[x][it->second] = true;
            x = it->second;
        }
        ans = max(ans, len);
    }

    printf("%d\n", ans);
    return 0;
}