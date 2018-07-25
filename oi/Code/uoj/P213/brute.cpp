#include <cstdio>
#include <cstring>
#include <climits>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 1000000

typedef long long i64;

static int n;
static i64 seq[NMAX + 10];

int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%lld", seq + i);
    }

    i64 ans = 0;
    for (int m = 1; m <= n; m++) {
        i64 sum = 0;
        deque<int> q;
        for (int i = 1; i <= n; i++) {
            while (!q.empty() && seq[q.back()] <= seq[i])
                q.pop_back();
            q.push_back(i);
            if (i - q.front() >= m)
                q.pop_front();
            if (i >= m)
                sum += seq[q.front()];
        }

        printf("%d: %lld\n", m, sum);
        ans ^= sum % 998244353;
    }

    printf("%lld\n", ans);
    return 0;
}
