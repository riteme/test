#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>

using namespace std;

#define NMAX 100000

typedef long long i64;

int n, m, q;
int a[NMAX + 10];

int find(int x) {
    return a[x] > 0 ? a[x] = find(a[x]) : x;
}

void _main() {
    for (int i = 1; i <= n; i++) {
        a[i] = INT_MIN;
    }

    for (int i = 0; i < m; i++) {
        int v, x;
        scanf("%d%d", &v, &x);
        x++;
        a[x] = max(a[x], -v);
    }

    while (q--) {
        char op[4];
        scanf("%s", op);

        if (op[0] == 'G') {
            int x;
            scanf("%d", &x);
            x++;

            if (a[x] > 0) {
                int z = find(x);
                printf("Company %d is a part of company %d.\n", x - 1, z - 1);
            } else {
                if (a[x] == INT_MIN)
                    printf("Company %d is empty.\n", x - 1);
                else
                    printf("Lowest rate: %d.\n", -a[x]);
            }
        } else if (op[0] == 'A') {
            int v, x;
            scanf("%d%d", &v, &x);
            x++;

            if (a[x] > 0)
                puts("Reject");
            else {
                puts("Accept");
                a[x] = max(a[x], -v);
            }
        } else {
            int x, y;
            scanf("%d%d", &x, &y);
            x++;
            y++;

            if (x == y || a[x] > 0 || a[y] > 0)
                puts("Reject");
            else {
                puts("Accept");
                a[x] = max(a[x], a[y]);
                a[y] = x;
            }
        }
    }
}

int main() {
    while (scanf("%d%d%d", &n, &m, &q) != EOF) {
        _main();
        puts("");
    }
    return 0;
}
