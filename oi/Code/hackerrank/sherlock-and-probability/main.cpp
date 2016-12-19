#include <cstdio>
#include <cstring>

#include <deque>
#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long int64;

inline int64 gcd(int64 a, int64 b) {
    while (b) {
        int64 tmp = a % b;
        a = b;
        b = tmp;
    }

    return a;
}

static int n, k;
static char seq[NMAX + 10];

int main() {
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d", &n, &k);
        scanf("%s", seq + 1);

        int64 ok = 0;
        deque<int> q;
        for (int i = 1; i <= n; i++) {
            if (seq[i] == '1') {
                while (!q.empty() && i - q.front() > k) {
                    q.pop_front();
                }

                ok += q.size() * 2 + 1;

                q.push_back(i);
            }
        }

        int64 all = static_cast<int64>(n) * n;
        int64 factor = gcd(ok, all);
        printf("%lld/%lld\n", ok / factor, all / factor);
    }

    return 0;
}
