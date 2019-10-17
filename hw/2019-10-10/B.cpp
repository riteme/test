#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, L, K;
static int a[NMAX + 10];

int main() {
    scanf("%d%d%d", &n, &K, &L);
    int ans = 0;
    deque<int> q;
    for (int i = 1; i <= n; i++) {
        scanf("%d", a + i);
        while (!q.empty() && a[q[0]] <= a[i])
            q.pop_front();
        q.push_front(i);
        if (q.back() <= i - L)
            q.pop_back();
        if (i >= L && a[q.back()] <= K)
            ans++;
    }
    printf("%d\n", ans);

    return 0;
}
