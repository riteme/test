#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <climits>
#include <algorithm>

#define NMAX 100000

static int n;
static int num[NMAX + 10];
static int s[NMAX + 10];

inline void modify(int left, int right, int v) {
    for (int x = right; x; x -= x & (-x))
        s[x] += v;
    for (int x = left - 1; x; x -= x & (-x))
        s[x] -= v;
}

inline int query(int x) {
    int answer = 0;

    for (int i = x; i <= n; i += i & (-i))
        answer += s[i];

    return answer + num[x];
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", num + i);
    }  // for

    int q;
    scanf("%d", &q);
    for (int i = 1; i <= q; i++) {
        int command;
        scanf("%d", &command);

        if (command == 1) {
            int l, r, v;
            scanf("%d%d%d", &l, &r, &v);

            modify(l, r, v);
        } else {
            int x;
            scanf("%d", &x);

            printf("%d\n", query(x));
        }
    }  // for

    return 0;
}  // function main
