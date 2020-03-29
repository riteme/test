#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100
#define AMAX 25000

int a[NMAX + 10];
bool ok[AMAX + 10];

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
            scanf("%d", a + i);
        sort(a, a + n);

        int m = a[n - 1], cnt = 0;
        memset(ok + 1, 0, m);
        ok[0] = true;
        for (int i = 0; i < n; i++) if (!ok[a[i]]) {
            cnt++;
            for (int j = 0; j + a[i] <= m; j++)
                ok[j + a[i]] |= ok[j];
        }

        printf("%d\n", cnt);
    }
    return 0;
}