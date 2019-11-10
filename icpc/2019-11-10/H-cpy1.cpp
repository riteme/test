#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int n;
static int C[NMAX + 10], L[NMAX + 10];
static i64 mx[NMAX + 10];

int main() {
    scanf("%d", &n);
    for (int i = 1; i < n; i++)
        scanf("%d", C + i);
    for (int i = 1; i < n; i++)
        scanf("%d", L + i);

    mx[n] = C[n];
    deque<i64> q;
    q.push_front(n);
    for (int i = n - 1; i >= 1; i--) {
        int l = 0, r = q.size() - 1;
        while (l < r) {
            int mi = (l + r) / 2 + 1;
            if (q[mi] <= i + L[i]) l = mi;
            else r = mi - 1;
        }
        mx[i] = C[i] + mx[l];
        while (!q.empty() && mx[i] >= mx[q[0]])
            q.pop_front();
        q.push_front(i);
    }

    printf("%lld ", mx[1]);

    return 0;
}
