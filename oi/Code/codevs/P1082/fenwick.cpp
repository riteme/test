#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

using namespace std;

#define NMAX 200000

typedef long long ntype;

static int n;
static ntype b[NMAX + 10];
static ntype c[NMAX + 10];

inline void modify(int r, ntype v) {
    if (r < 1)
        return;

    for (int i = r; i; i -= i & (-i))
        b[i] += v;
    for (int i = r; i <= n; i += i & (-i))
        c[i] += v * r;
}

inline ntype query(int r) {
    if (r < 1)
        return 0;

    ntype answer = 0;

    for (int i = r; i <= n; i += i & (-i))
        answer += b[i];
    answer *= r;
    for (int i = r - 1; i; i -= i & (-i))
        answer += c[i];

    return answer;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        ntype x;
        scanf("%lld", &x);

        modify(i, x);
        modify(i - 1, -x);
    }  // for

    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int command;
        scanf("%d", &command);

        if (command == 1) {
            int l, r;
            ntype v;
            scanf("%d%d%lld", &l, &r, &v);

            modify(r, v);
            modify(l - 1, -v);
        } else {
            int l, r;
            scanf("%d%d", &l, &r);

            printf("%lld\n", query(r) - query(l - 1));
        }
    }  // for

    return 0;
}  // function main
