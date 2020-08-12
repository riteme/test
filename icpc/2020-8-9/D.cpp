#include <cstdio>
#include <cstring>

#include <algorithm>

using namespace std;

#define NMAX 200000

struct node_t {
    int idx, deg;

    bool operator<(const node_t &z) const {
        return deg < z.deg;
    }
};

int n;
node_t w[NMAX + 10];

int main() {
    scanf("%d", &n);
    if (n == 2) {
        puts("1 2");
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        scanf("%d", &w[i].deg);
        w[i].idx = i;
    }
    sort(w + 1, w + n + 1);

    int j = 1;
    while (w[j].deg == 1) {
        j++;
    }
    for (int i = 1; i < n; i++) {
        printf("%d %d\n", w[i].idx, w[j].idx);
        w[j].deg--;
        if (j < n && w[j].deg == 1)
            j++;
    }

    return 0;
}
