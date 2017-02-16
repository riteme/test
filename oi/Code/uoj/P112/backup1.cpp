#include <cctype>
#include <climits>
#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

static int k, n;
static i64 L[NMAX + 10];
static i64 R[NMAX + 10];
static i64 contrib;
static struct {
    i64 val;
    int index;

    template <typename T>
    bool operator<(const T &b) const {
        return val < b.val;
    }
} P[NMAX * 2 + 10];

namespace Solver1 {

i64 main() {
    i64 ans, sum = 0, lcnt = 0, rcnt = n - 1;
    for (int i = 1; i <= n; i++) {
        sum += abs(R[i] - P[1].val) + abs(L[i] - P[1].val);
    }  // for
    ans = sum;

    for (int i = 2; i <= 2 * n; i++) {
        i64 p = P[i].val;
        int index = P[i].index;
        i64 delta = p - P[i - 1].val;
        sum += (lcnt - rcnt) * delta * 2;

        if (p == L[index])
            rcnt--;
        else if (p == R[index])
            lcnt++;

        ans = min(ans, sum);
    }  // for

    return ans;
}

}  // namespace Solver1

namespace Solver2 {

i64 evaluate(i64 p1, i64 p2) {
    i64 sum = 0;

    for (int i = 1; i <= n; i++) {
        sum += min(abs(L[i] - p1) + abs(R[i] - p1),
                   abs(L[i] - p2) + abs(R[i] - p2));
    }  // for

    return sum;
}

i64 main() {
    i64 ans = LLONG_MAX;

    for (int i = 1; i <= 2 * n; i++) {
        for (int j = i + 1; j <= 2 * n; j++) {
            ans = min(ans, evaluate(P[i].val, P[j].val));
        }  // for
    }      // for

    return ans;
}

}  // namespace Solver2

inline char get_valid_char() {
    char c = getchar();

    while (!isalpha(c)) {
        c = getchar();
    }  // while

    return c;
}

void initialize() {
    scanf("%d%d", &k, &n);

    for (int i = 1; i <= n; i++) {
        char ida, idb;
        i64 p1, p2;
        ida = get_valid_char();
        scanf("%lld", &p1);
        idb = get_valid_char();
        scanf("%lld", &p2);

        if (p1 > p2)
            swap(p1, p2);

        if (ida == idb) {
            contrib += p2 - p1;
            i--, n--;
        } else {
            L[i] = p1, R[i] = p2;
            P[2 * i - 1] = {p1, i};
            P[2 * i] = {p2, i};
        }
    }  // for

    sort(P + 1, P + 2 * n + 1);
}

int main() {
    initialize();

    if (n == 0)
        printf("%lld\n", contrib);
    else if (k == 1)
        printf("%lld\n", Solver1::main() + contrib + n);
    else
        printf("%lld\n", Solver2::main() + contrib + n);

    return 0;
}  // function main
