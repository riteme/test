#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 100000

static int n, q;
static int H[NMAX + 10];

static void initialize() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++) {
        scanf("%d", H + i);
    }
}

inline int query_max(int left, int right) {
    int result = 0;

    for (int i = left; i < right; i++) {
        for (int j = i + 1; j <= right; j++) {
            result = max(result, H[i] - H[j]);
        }
    }

    return result;
}

int main() {
    initialize();

    scanf("%d", &q);

    char command[10];
    while (q--) {
        scanf("%s", command);

        if (command[0] == 'M') {
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);

            for (int i = l; i <= r; i++) {
                H[i] += x;
            }
        } else {
            int l, r;
            scanf("%d%d", &l, &r);

            int m = query_max(l, r);
            printf("%d\n", m);

            if (m > 0)
                H[++n] = m;
        }
    }

    return 0;
}

