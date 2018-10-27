#include <cstdio>
#include <cstring>

#include <vector>
#include <algorithm>

using namespace std;

#define NMAX 100000

inline int c2(int n) {
    return n * (n - 1) >> 1;
}

static vector<int> buc[NMAX + 10];

int main() {
    int n;
    scanf("%d", &n);
    int k = 1;
    for (; c2(k + 1) <= n; k++) ;
    if (c2(k) == n) {
        for (int t = 1, l = 1, p = 1; t <= n; t++, p++) {
            buc[p].push_back(t);
            buc[p + l].push_back(t);
            if (p + l == k) {
                l++;
                p = 0;
            }
        }
        puts("Yes");
        printf("%d\n", k);
        for (int i = 1; i <= k; i++) {
            printf("%zu ", buc[i].size());
            for (int v : buc[i]) printf("%d ", v);
            puts("");
        }
    } else puts("No");
    return 0;
}
