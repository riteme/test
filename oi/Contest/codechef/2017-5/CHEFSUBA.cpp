#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 200000

static int n, k, p;
static deque<int> q;
static int pos;
static int a[NMAX + 10];
static int ans[NMAX + 10];

void shift(int v) {
    pos++;
    a[pos] = v;
    ans[pos] = ans[pos - 1] + v - a[max(0, pos - k)];

    if (!q.empty() && q.front() <= pos - n + k - 1)
        q.pop_front();

    while (!q.empty() && ans[q.back()] <= ans[pos])
        q.pop_back();
    q.push_back(pos);
}

int main() {
    // freopen("data.in", "r", stdin);
    scanf("%d%d%d", &n, &k, &p);
    k = min(k, n);

    for (int i = n; i >= 1; i--) {
        scanf("%d", a + i);
    }

    for (int i = 1; i <= n; i++) {
        shift(a[i]);
    }

    while (p--) {
        char command = getchar();
        while (command != '?' && command != '!')
            command = getchar();

        if (command == '?')
            printf("%d\n", ans[q.front()]);
        else
            shift(a[pos - n + 1]);
    }

    return 0;
}
