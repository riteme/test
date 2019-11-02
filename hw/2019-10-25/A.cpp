#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 2000000

static int n;
static int a[NMAX + 10];

int main() {
    while (scanf("%d", &n) != EOF) {
        if (!n) break;
        for (int i = 1; i <= n; i++)
            scanf("%d", a + i);
        memcpy(a + n + 1, a + 1, sizeof(int) * n);
        for (int i = 1; i <= 2 * n; i++)
            a[i] += a[i - 1];
        deque<int> q;
        int ans = 0;
        for (int i = 1; i <= 2 * n - 1; i++) {
            while (!q.empty() && a[q.back()] >= a[i])
                q.pop_back();
            q.push_back(i);
            if (q[0] <= i - n) q.pop_front();
            if (i >= n)
                ans += a[q[0]] >= a[i - n];
        }
        printf("%d\n", ans);
    }
    return 0;
}
