#include <cstdio>
#include <cstring>
#include <climits>

#include <algorithm>
#include <unordered_set>

using namespace std;

#define NMAX 1000000

int n, q;
int a[NMAX + 10], b[NMAX + 10];

int main() {
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; i++)
        scanf("%d", a + i);
    b[n + 1] = INT_MAX;
    for (int i = n; i >= 1; i--)
        b[i] = min(a[i], b[i + 1]);

    while (q--) {
        int op, x, v;
        scanf("%d", &op);
        if (op == 1) {
            scanf("%d%d", &x, &v);
            a[x] = v;
            for (int i = x; i >= 1; i--)
                b[i] = min(a[i], b[i + 1]);
        } else {
            scanf("%d", &x);
            unordered_set<int> mp;
            for (int i = x; i <= n; i++)
                mp.insert(b[i]);
            printf("%zu\n", mp.size());
        }
    }

    return 0;
}