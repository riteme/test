#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>
#include <deque>

using namespace std;

#define NMAX 1000000

typedef long long i64;

static int n;
static i64 a[NMAX + 10];
static deque<int> q1, q2;

void initialize() {
    i64 sum = 0;
    for (int i = 0; i < n; i++) {
        scanf("%lld", a + i);
        sum += a[i];
    }

    sum /= n;
    for (int i = 0; i < n; i++) {
        a[i] -= sum;
    }

    q1.clear();
    q2.clear();
    for (int i = 0; i < n / 2; i++) {
        if (a[i] > 0)
            q1.push_back(i);
    }

    for (int i = n / 2; i < n; i++) {
        if (a[i] > 0)
            q2.push_front(i);
    }
}

inline i64 dist(int i, int j) {
    if (i < 0 || j < 0)
        return LLONG_MAX;
    if (i > j)
        swap(i, j);

    return min(j - i, i + n - j);
}

int main() {
    while (scanf("%d", &n) != EOF) {
        initialize();

        i64 ans = 0;
        for (int i = 0; i < n; i++) {
            while (a[i] < 0) {
                int j = -1;
                if (!q1.empty() && dist(i, j) > dist(i, q1[0]))
                    j = q1[0];
                if (!q2.empty() && dist(i, j) > dist(i, q2[0]))
                    j = q2[0];
                
                ans += min(a[j], -a[i]) * dist(i, j);

                if (-a[i] < a[j]) {
                    a[j] += a[i];
                    a[i] = 0;
                } else {
                    a[i] += a[j];
                    a[j] = 0;

                    if (q1[0] == j)
                        q1.pop_front();
                    else
                        q2.pop_front();
                }
            }

            if (!q1.empty() && q1[0] == i) {
                q2.push_front(i);
                q1.pop_front();
            }

            if (!q2.empty() && q2.back() == n / 2) {
                q1.push_back(n / 2);
                q2.pop_back();
            }
        }

        printf("%lld\n", ans);
    }

    return 0;
}
